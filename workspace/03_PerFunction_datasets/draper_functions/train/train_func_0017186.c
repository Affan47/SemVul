se_ForceSpectate( REAL & time, REAL minTime, char const * message, char const * & cantPlayMessage, int & experienceNeeded )
{
    if ( time < 0 )
    {
        time = 0;
    }

    if ( time >= minTime )
    {
        return false;
    }
    else
    {


        int needed = int( minTime - time + 2 );
        if ( needed > experienceNeeded )
        {
            experienceNeeded = needed;
        }
        cantPlayMessage = message;

        return true;
    }
}
