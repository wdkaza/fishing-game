#include "raylib.h"

// i dont like this code at all a bunch of if else statements looks bad not proud of it at all
// time to complete ~2 hours

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;


    float playerSpeed = 0;
    float playerX = 350; 
    float maxSpeed = 10;
    float acceleration = 0.2f;

    float fishSpeed = 0;
    float fishX = 390; 
    // float fishacceleration;
    // float fishDashTime;

    float progress = 50.0f;
    const float maxProgress = 100.0f;
    float progressIncreaseSpeed = 0.5f;
    float progressDecresseSpeed = 1.0f; //whatever you spell it


    int catchStreak = 0;



    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    while(!WindowShouldClose()) 
    {
        // Update
        //----------------------------------------------------------------------------------

        //
        //hitboxes
        //

        Rectangle playerHitbox = {
            playerX,                    
            GetScreenHeight()/2-38,     
            200,                        
            70                          
        };
        
        Rectangle fishHitbox = {
            fishX,                      
            GetScreenHeight()/2-38,     
            10,                         
            70                          
        };

        bool collision = CheckCollisionRecs(playerHitbox, fishHitbox);

        //
        //  PLAYER CODE
        //

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            playerSpeed = playerSpeed + acceleration;
            if (playerSpeed > maxSpeed) playerSpeed = maxSpeed;
        }
        else
        {
            playerSpeed = playerSpeed - acceleration;
            if (playerSpeed < -maxSpeed) playerSpeed = -maxSpeed;
        }

        playerX += playerSpeed;

        if (playerX < 50) 
        {
            playerX = 50;
            playerSpeed = 0;
        }
        if (playerX > 675)
        {
            playerX = 675;
            playerSpeed = 0;
        }


 
        playerX += playerSpeed;

    
        if (playerX < 50) 
        {
            playerX = 50;
            playerSpeed = 0;
        }
        if (playerX > 550)
        {
            playerX = 550;
            playerSpeed = 0;
        }

        //
        //  FISH CODE
        //

        // fishacceleration = GetRandomValue(0.05f,0.2f);
        // fishDashTime = GetRandomValue(1,2);
        int whatSide = GetRandomValue(1,2);
        
        if(whatSide == 1){
            fishSpeed = fishSpeed + acceleration;
            if(fishSpeed > maxSpeed) fishSpeed = maxSpeed;
        }
        else // i have no idea why it works well and i do not mind im just gonna lveave it like that
        {
            fishSpeed = fishSpeed - acceleration;
            if (fishSpeed < -maxSpeed) fishSpeed = -maxSpeed;
        }

        fishX += fishSpeed;

        if (fishX < 50) 
        {
            fishX = 50;
            fishSpeed = 0;
        }
        if (fishX > 550)
        {
            fishX = 550;
            fishSpeed = 0;
        }


        //
        //  PROGRESS BAR CODE
        //
        
        if(collision){
            progress =  progress + progressIncreaseSpeed;
        }
        else{
            progress = progress - progressDecresseSpeed;
        }
        if(progress >= maxProgress){
            progress = 25.0f;
            fishX = 390;
            playerX = 350;
            playerSpeed = 0;
            catchStreak++;
        }
        if(progress <= 0){
            progress = 25.0f;
            fishX = 390;
            playerX = 350;
            playerSpeed = 0;
            catchStreak = 0;
            progressIncreaseSpeed = 0.5f;
            progressDecresseSpeed = 1.0f;
            acceleration = 0.2f;
        }

        //
        // BOSS LVL FISH(eveyr fifth lvl)
        //
        

        

                
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(DARKBLUE);
            //
            // draws the main bar
            DrawRectangle(50, GetScreenHeight()/2-40, 700, 75,BLUE);

            //draws the player bar
            DrawRectangle(playerX, GetScreenHeight()/2-38,200,70,(IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? GRAY : DARKGRAY));

            //draws fish bar
            DrawRectangle(fishX, GetScreenHeight()/2-38,10,70,DARKGREEN);

            Rectangle rect = {50, GetScreenHeight()/2-40, 700, 75};
            DrawRectangleLinesEx(rect, 3.0f, RED);

            //progress bar
            DrawRectangle(150, GetScreenHeight()/2+50,(int)((progress/maxProgress) * 500), 40, BLUE);

            Rectangle rect1 = {150, GetScreenHeight()/2+50, 500, 40};
            DrawRectangleLinesEx(rect1, 3.0f, RED);


            //collision no collosiion texxt
            DrawText(collision ? "COLLISION!" : "NO COLLISION", 10, 10, 20, WHITE);

            //catch streak text
            DrawText(TextFormat("Catch Streak: %03i", catchStreak), 300, 100, 20, WHITE);


            //

        EndDrawing();

    }

    CloseWindow();

    return 0;
}