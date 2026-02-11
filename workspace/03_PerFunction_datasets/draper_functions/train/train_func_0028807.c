us_net_wait_readable_list( struct timeval *cur_time,
                               struct timeval *wake_up_time,
                               uint32_t next_wake_up_delta_time_milliseconds,
                               int fd_count,
                               const int *fds )
{
    int r = -1;
    int n = 0;
    fd_set readable_set;
    struct timeval tv_timeout;
    int max_fd = -1;
    int i;

    if ( cur_time->tv_sec == 0 && cur_time->tv_usec == 0 )
    {
        gettimeofday( cur_time, 0 );
        us_net_timeout_add( wake_up_time, cur_time, next_wake_up_delta_time_milliseconds * 1000 );
    }

    us_net_timeout_calc( &tv_timeout, cur_time, wake_up_time );

    FD_ZERO( &readable_set );
    for ( i = 0; i < fd_count; ++i )
    {
        int fd = fds[i];
        if ( fd != -1 )
        {
            FD_SET( fd, &readable_set );
            if ( fd > max_fd )
            {
                max_fd = fd;
            }
        }
    }
    do
    {
        n = select( max_fd + 1, &readable_set, 0, 0, &tv_timeout );
    } while ( n < 0 && ( errno == EINTR ) );

    gettimeofday( cur_time, 0 );

    if ( n < 0 )
    {
        r = -2;
    }
    else if ( n == 0 )
    {
        r = -1;
    }
    else if ( n > 0 )
    {
        r = -1;
        for ( i = 0; i < max_fd + 1; i++ )
        {
            if ( FD_ISSET( i, &readable_set ) )
            {
                r = i;
                break;
            }
        }
    }
    if ( us_net_timeout_hit( cur_time, wake_up_time ) )
    {
        us_net_timeout_add( wake_up_time, wake_up_time, next_wake_up_delta_time_milliseconds );
    }

    return r;
}
