#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char** argv)
{
    int GAMEPAD_INDEX = 0;
    
    if(argc > 1)
    {
        GAMEPAD_INDEX = atoi(argv[1]);
    }
    
    const Uint64 freq = SDL_GetPerformanceFrequency();
    Uint64 start = SDL_GetPerformanceCounter();
    Uint64 end;
    
    printf("Gamepad test: %d\n", GAMEPAD_INDEX);
    
    SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC);
    
    SDL_Joystick* joystick = SDL_JoystickOpen(GAMEPAD_INDEX);
    
    printf("Opened joystick `%s`\n", SDL_JoystickName(joystick));
    
    SDL_Haptic* haptic = SDL_HapticOpenFromJoystick(joystick);
    int hapticSuccess;
    
    if(haptic == NULL)
    {
        printf("Could not open haptic\n");
    }
    else
    {
        hapticSuccess = SDL_HapticRumbleInit(haptic);
    }
    
    end = SDL_GetPerformanceCounter();
    
    float seconds = (float)(end - start) / (float)freq;
    
    printf("Opening haptic took %f seconds\n", seconds);
    
    if(haptic == NULL)
    {
        return 0;
    }
    
    printf("Success: %d. Rumbling...\n", hapticSuccess);
    
    hapticSuccess = SDL_HapticRumblePlay(haptic, 1.0f, 500);
    
    SDL_Delay(500);
    
    printf("Success: %d. Rumble over. Goodbye!\n", hapticSuccess);
    
    return 0;
}
