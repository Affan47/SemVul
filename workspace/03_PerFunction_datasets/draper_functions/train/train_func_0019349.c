DrawWorldTimer(void)
{
    int days;
    int hours;
    int minutes;
    int seconds;
    int worldTimer;
    char timeBuffer[15];
    char dayBuffer[20];

    worldTimer = players[consoleplayer].worldTimer;

    worldTimer /= 35;
    days = worldTimer / 86400;
    worldTimer -= days * 86400;
    hours = worldTimer / 3600;
    worldTimer -= hours * 3600;
    minutes = worldTimer / 60;
    worldTimer -= minutes * 60;
    seconds = worldTimer;

    sprintf(timeBuffer, "%.2d : %.2d : %.2d", hours, minutes, seconds);
    MN_DrTextA(timeBuffer, 240, 8);

    if (days)
    {
        if (days == 1)
        {
            sprintf(dayBuffer, "%.2d DAY", days);
        }
        else
        {
            sprintf(dayBuffer, "%.2d DAYS", days);
        }
        MN_DrTextA(dayBuffer, 240, 20);
        if (days >= 5)
        {
            MN_DrTextA("YOU FREAK!!!", 230, 35);
        }
    }
}
