#include <stdio.h>

void initializeSystem(int lights[], int temps[], int motions[], int locks[], int rooms);
void toggleLight(int lights[], int rooms);
void readTemperature(int temps[], int rooms);
void detectMotion(int motions[], int rooms);
void controlSecurity(int locks[], int rooms);
void houseStatus(int lights[], int temps[], int motions[], int locks[], int rooms);
void autoLock(int motions[], int locks[], int rooms, int *motionCounter);
void energySavingMode(int lights[], int rooms, int *lightCounter);
void temperatureAlert(int temps[], int rooms);

int main() {
    int rooms, choice, motionCounter = 0, lightCounter = 0;
    
    printf("Enter number of rooms: ");
    scanf("%d", &rooms);
    
    int lights[rooms], temps[rooms], motions[rooms], locks[rooms];
    
    initializeSystem(lights, temps, motions, locks, rooms);
    
    while (1) {
        printf("\n===== Smart Home Menu =====\n");
        printf("1. Toggle Light\n");
        printf("2. Read Temperature\n");
        printf("3. Check Motion Sensor\n");
        printf("4. Lock/Unlock Security System\n");
        printf("5. House Status Summary\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                toggleLight(lights, rooms);
                lightCounter++;
                energySavingMode(lights, rooms, &lightCounter);
                break;
            case 2:
                readTemperature(temps, rooms);
                temperatureAlert(temps, rooms);
                break;
            case 3:
                detectMotion(motions, rooms);
                autoLock(motions, locks, rooms, &motionCounter);
                break;
            case 4:
                controlSecurity(locks, rooms);
                break;
            case 5:
                houseStatus(lights, temps, motions, locks, rooms);
                break;
            case 6:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

void initializeSystem(int lights[], int temps[], int motions[], int locks[], int rooms) {
    for (int i = 0; i < rooms; i++) {
        lights[i] = 0;
        temps[i] = 22 + (i % 5); 
        motions[i] = 0;
        locks[i] = 1;
    }
    printf("Initializing system...\n");
}

void toggleLight(int lights[], int rooms) {
    int room;
    printf("Enter room number to toggle light (1-%d): ", rooms);
    scanf("%d", &room);
    if (room >= 1 && room <= rooms) {
        lights[room - 1] = !lights[room - 1];
        printf("Light in Room %d is now %s.\n", room, lights[room - 1] ? "ON" : "OFF");
    } else {
        printf("Invalid room number.\n");
    }
}

void readTemperature(int temps[], int rooms) {
    int room;
    printf("Enter room number to check temperature (1-%d): ", rooms);
    scanf("%d", &room);
    if (room >= 1 && room <= rooms) {
        printf("Room %d Temperature: %d°C\n", room, temps[room - 1]);
    } else {
        printf("Invalid room number.\n");
    }
}

void detectMotion(int motions[], int rooms) {
    int room;
    printf("Enter room number to check motion (1-%d): ", rooms);
    scanf("%d", &room);
    if (room >= 1 && room <= rooms) {
        printf("Motion in Room %d: %s\n", room, motions[room - 1] ? "Detected" : "No Motion");
    } else {
        printf("Invalid room number.\n");
    }
}

void controlSecurity(int locks[], int rooms) {
    int room;
    printf("Enter room number to lock/unlock (1-%d): ", rooms);
    scanf("%d", &room);
    if (room >= 1 && room <= rooms) {
        locks[room - 1] = !locks[room - 1];
        printf("Room %d is now %s.\n", room, locks[room - 1] ? "Locked" : "Unlocked");
    } else {
        printf("Invalid room number.\n");
    }
}

void houseStatus(int lights[], int temps[], int motions[], int locks[], int rooms) {
    printf("\nHouse Status:\n");
    for (int i = 0; i < rooms; i++) {
        printf("Room %d: Light %s, Temp %d°C, %s, %s\n", i + 1, 
               lights[i] ? "ON" : "OFF", temps[i],
               motions[i] ? "Motion Detected" : "No Motion", 
               locks[i] ? "Locked" : "Unlocked");
    }
}

void autoLock(int motions[], int locks[], int rooms, int *motionCounter) {
    (*motionCounter)++;
    if (*motionCounter >= 5) {
        for (int i = 0; i < rooms; i++) {
            if (!motions[i]) {
                locks[i] = 1;
            }
        }
        printf("Auto-Lock Activated: All rooms with no motion are locked.\n");
        *motionCounter = 0;
    }
}

void energySavingMode(int lights[], int rooms, int *lightCounter) {
    if (*lightCounter >= 5) {
        printf("Energy Saving Mode: Consider turning off some lights.\n");
        *lightCounter = 0;
    }
}

void temperatureAlert(int temps[], int rooms) {
    for (int i = 0; i < rooms; i++) {
        if (temps[i] > 30) {
            printf("Warning: Room %d Temperature is above 30°C!\n", i + 1);
        }
    }
}

