#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <algorithm>
#include <vector>
using namespace std;


//Создайте игру «МорскойБой».
//Главные особенности реализации игры : 
//Режимы игры Человек - компьютер Компьютер - компьютер 
//Расстановка кораблей Игрок расставляет вручную Компьютер расставляет за игрока 
//Компьютер может играть в двух режимах Случайный выстрел Интеллектуальная игра.
//Компьютер строит стратегию игры, а не стреляет случайно 
//Отображать текущее состояние игрового поля игрока и компьютера 
//Возможность остановки, приостановки, нового запуска игры


const int SIZE = 10;  

struct Point {
    int x;
    int y;
};
class BattleshipGame 
{
private:
    char playerBoard[SIZE][SIZE];    
    char computerBoard[SIZE][SIZE]; 
    bool isPlayerTurn;               

public:
    BattleshipGame() {
       
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                playerBoard[i][j] = ' ';
                computerBoard[i][j] = ' ';
            }
        }
    }

  
    void setPlayerShips() {
        cout << "Arrange your ships on the playing field.\n";
        cout << "Enter coordinates for each ship (A1 to J10).\n";
        cout << "Ships occupy one space each.\n";

        int shipsPlaced = 0;
        while (shipsPlaced < 5) {
            string input;
            cout << "Enter coordinates for the ship:" << shipsPlaced + 1 << ": ";
            cin >> input;

        
            if (input.length() != 2 || !isalpha(input[0]) || !isdigit(input[1])) {
                cout << "Incorrect coordinates. Try again.\n";
                continue;
            }

            int x = toupper(input[0]) - 'A';
            int y = input[1] - '0' - 1;

           
            if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
                cout << "Incorrect coordinates. Try again.\n";
                continue;
            }

           
            if (playerBoard[x][y] != ' ') {
                cout << "There is already a ship on this space. Try again.\n";
                continue;
            }

            playerBoard[x][y] = 'X';  
            shipsPlaced++;
        }
    }

    void setComputerShips() {
        cout << "The computer arranges its ships...\n";

        int shipsPlaced = 0;
        while (shipsPlaced < 5) {
            int x = rand() % SIZE;
            int y = rand() % SIZE;

            if (computerBoard[x][y] == ' ') {
                computerBoard[x][y] = 'X';
                shipsPlaced++;
            }
        }
    }

    void displayBoards() {
        cout << "Your playing field:\n";
        displayBoard(playerBoard);

        cout << "\nComputer playing field:\n";
        displayBoard(computerBoard);
    }

    void displayBoard(char board[SIZE][SIZE]) {
        cout << "   ";
        for (int i = 0; i < SIZE; i++) {
            cout << char('A' + i) << " ";
        }
        cout << endl;

        for (int i = 0; i < SIZE; i++) {
            cout << setw(2) << i + 1 << " ";
            for (int j = 0; j < SIZE; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }

 
    void play() {
        cout << "The game has begun!\n";
        bool gameOver = false;
        isPlayerTurn = true;

        while (!gameOver) {
            if (isPlayerTurn) {
              
                cout << "Your turn. Enter the coordinates for the shot:";
                string input;
                cin >> input;

               
                if (input.length() != 2 || !isalpha(input[0]) || !isdigit(input[1])) {
                    cout << "Incorrect coordinates. Try again.\n";
                    continue;
                }

                int x = toupper(input[0]) - 'A';
                int y = input[1] - '0' - 1;

              
                if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
                    cout << "Incorrect coordinates. Try again.\n";
                    continue;
                }

              
                if (computerBoard[x][y] != ' ') {
                    cout << "You have already shot at this cell. Try again.\n";
                    continue;
                }

              
                if (computerBoard[x][y] == 'X') {
                    cout << "You hit!\n";
                    computerBoard[x][y] = 'X';
                }
                else {
                    cout << "You missed(((.\n";
                    computerBoard[x][y] = '-';
                }
                isPlayerTurn = false; 

               
                if (checkGameOver()) {
                    cout << "You won! Congratulations!\n";
                    gameOver = true;
                    break;
                }
            }
            else {
                
                cout << "Computer move...\n";

               
                int mode = rand() % 2; 

                if (mode == 0) {
                    
                    Point target = getRandomTarget();
                    int x = target.x;
                    int y = target.y;

                    if (playerBoard[x][y] == 'X') {
                        cout << "The computer got into your ship!\n";
                        playerBoard[x][y] = 'X';
                    }
                    else {
                        cout << "The computer failed.\n";
                        playerBoard[x][y] = '-';
                    }
                }
                isPlayerTurn = true;

                if (checkGameOver()) {
                    cout << "The computer won!\n";
                    gameOver = true;
                }
            }
            displayBoards();
        }
    }
    bool checkGameOver() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (playerBoard[i][j] == 'X') {
                    return false;  
                }
                if (computerBoard[i][j] == 'X') {
                    return false;  
                }
            }
        }
        return true; 
    }

    Point getRandomTarget() {
        Point target;
        target.x = rand() % SIZE;
        target.y = rand() % SIZE;
        return target;
    }
};


int main() {
    srand(time(0));
    BattleshipGame game;
    game.setPlayerShips();
    game.setComputerShips();
    game.displayBoards();
    game.play();

    return 0;
}


//Создайте игру  «Память».
//Главные особенности реализации игры:
//Выбор размера поля.
//Начальная расстановка карт выполняется компьютером.
//Звуковое сопровождение игры.
//Если карты совпали звучит один звук.
//Если карты не совпали звучит другой звук.
//Статистика: Время игры Количество переворотов карт.

void clearScreen()
{
    cout << "\033[2J\033[1;1H" << endl;
}

void delay(int milliseconds)
{
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

void playMatchSound()
{
    cout << "\a";
    delay(500);
}

void playMismatchSound()
{
    cout << "\a";
    delay(1000);
}

class MemoryGame
{
private:
    int gridSize;
    vector<char> grid;
    vector<bool> flipped;
    int numFlipped;
    int numMatches;
    int numTurns;
    chrono::steady_clock::time_point startTime;

public:
    MemoryGame(int size) : gridSize(size), numFlipped(0), numMatches(0), numTurns(0)
    {
        grid.resize(gridSize);
        flipped.resize(gridSize, false);
        startTime = chrono::steady_clock::now();
    }

    void initializeGrid()
    {
        vector<char> values;
        for (int i = 0; i < gridSize / 2; ++i)
        {
            values.push_back('A' + i);
            values.push_back('A' + i);
        }

        srand(time(0));
        random_shuffle(values.begin(), values.end());

        for (int i = 0; i < gridSize; ++i)
        {
            grid[i] = values[i];
        }
    }

    void displayGrid()
    {
        clearScreen();
        for (int i = 0; i < gridSize; ++i)
        {
            if (flipped[i])
            {
                cout << grid[i] << " ";
            }
            else
            {
                cout << "* ";
            }

            if ((i + 1) % 4 == 0)
            {
                cout << endl;
            }
        }
    }

    void flipCard(int index)
    {
        if (!flipped[index])
        {
            flipped[index] = true;
            ++numFlipped;
        }
    }

    void hideFlippedCards() {
        for (int i = 0; i < gridSize; ++i)
        {
            if (flipped[i])
            {
                flipped[i] = false;
                --numFlipped;
            }
        }
    }

    void checkMatch() {
        vector<int> flippedIndices;
        for (int i = 0; i < gridSize; ++i)
        {
            if (flipped[i])
            {
                flippedIndices.push_back(i);
            }
        }

        if (flippedIndices.size() == 2) {
            ++numTurns;
            if (grid[flippedIndices[0]] == grid[flippedIndices[1]]) {
                playMatchSound();
                ++numMatches;
                flipped[flippedIndices[0]] = false;
                flipped[flippedIndices[1]] = false;
                numFlipped -= 2;
            }
            else {
                playMismatchSound();
                delay(1000);
                hideFlippedCards();
            }
        }
    }

    bool isGameOver()
    {
        return numMatches == gridSize / 2;
    }

    void getStats()
    {
        setlocale(LC_ALL, "rus");
        chrono::steady_clock::time_point endTime = chrono::steady_clock::now();
        chrono::duration<double> duration = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);

        cout << endl;
        cout << "======== ИГРА ОКОНЧЕНА! ========" << endl;
        cout << "ВРЕМЯ: " << duration.count() << " seconds" << endl;
        cout << "Количество ходов: " << numTurns << endl;
        cout << "============================" << endl;
    }
};

int main()
{
    setlocale(LC_ALL, "rus");
    int gridSize;
    cout << "Введите размер сетки (четное число от 4 до 16): " << endl;
    cin >> gridSize;

    if (gridSize < 4 || gridSize > 16 || gridSize % 2 != 0)
    {
        cout << "Неверный размер сетки. Выход..." << endl;
        return 0;
    }

    MemoryGame game(gridSize);
    game.initializeGrid();

    while (!game.isGameOver())
    {
        game.displayGrid();

        int index;
        cout << "Введите номер карты, которую нужно перевернуть (от 0 до" << gridSize - 1 << "): ";
        cin >> index;

        if (index < 0 || index >= gridSize)
        {
            cout << "Неверный индекс. Попробуйте еще раз." << endl;
            continue;
        }

        game.flipCard(index);
        game.checkMatch();
    }

    game.displayGrid();
    game.getStats();

    return 0;
}