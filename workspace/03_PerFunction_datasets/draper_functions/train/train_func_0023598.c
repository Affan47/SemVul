set_rollover_time()
{
    time_t now;
    struct tm *curtime;

    now = time(NULL);
    curtime = localtime(&now);

    switch(rollover_interval)
    {
        case MINUTES:
            curtime->tm_min += rollover;
            curtime->tm_sec = 0;
            break;
        case HOURS:
            curtime->tm_hour += rollover;
            curtime->tm_min = 0;
            curtime->tm_sec = 0;
            break;
        case DAYS:
            curtime->tm_mday += rollover;
            curtime->tm_hour = 0;
            curtime->tm_min = 0;
            curtime->tm_sec = 0;
            break;
    }
    nextroll = mktime(curtime);
    return 0;
}
