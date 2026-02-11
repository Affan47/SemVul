start_timer( gpointer clocklist )
{
    extern gint timer;
    gint newTimer;


    int beatInterval = 60000;


    static gboolean needsMinutesSyncedToSeconds = TRUE;


    time_t currenttime;
    struct tm humanReadableTime;


    if ( timer <= 0 )
	needsMinutesSyncedToSeconds = TRUE;


    if ( strstr( displayFormat->str, "%c" ) ||
	 strstr( displayFormat->str, "%N" ) ||
	 strstr( displayFormat->str, "%r" ) ||
	 strstr( displayFormat->str, "%s" ) ||
	 strstr( displayFormat->str, "%S" ) ||
	 strstr( displayFormat->str, "%T" ) ||
	 strstr( displayFormat->str, "%X" )   )
    {
	beatInterval = 1000;
	needsMinutesSyncedToSeconds = FALSE;
    }

    if ( needsMinutesSyncedToSeconds )
    {


	time(&currenttime);
	localtime_r( &currenttime, &humanReadableTime );

	beatInterval -=  humanReadableTime.tm_sec * 1000;
    }

    if ( needsMinutesSyncedToSeconds )
    {
	needsMinutesSyncedToSeconds = FALSE;
	newTimer = g_timeout_add( beatInterval, SetTimeAndSyncMinutes, clocklist);
    }
    else
	newTimer = g_timeout_add( beatInterval, SetTime, clocklist);

    return newTimer;
}
