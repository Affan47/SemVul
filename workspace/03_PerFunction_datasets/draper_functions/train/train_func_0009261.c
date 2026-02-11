us_net_timeout_calc( struct timeval *result, const struct timeval *cur_time, const struct timeval *next_time )
{
    bool r = false;
    if ( us_net_timeout_hit( cur_time, next_time ) )
    {

        result->tv_sec = 1;
        result->tv_usec = 0;
    }
    else
    {
        result->tv_sec = next_time->tv_sec - cur_time->tv_sec;
        result->tv_usec = next_time->tv_usec - cur_time->tv_usec;
        if ( result->tv_usec < 0 )
        {
            result->tv_usec += 1000000;
            result->tv_sec--;
        }
        r = true;
    }
    return r;
}
