linux_set_rate(struct wif *wi, int rate)
{
    struct priv_linux *dev = wi_priv(wi);
    struct ifreq ifr;
    struct iwreq wrq;
    char s[32];
    int pid, status, unused;

    memset(s, 0, sizeof(s));

    switch(dev->drivertype) {
    case DT_MADWIFING:
        memset( &ifr, 0, sizeof( ifr ) );
        strncpy( ifr.ifr_name, wi_get_ifname(wi), sizeof( ifr.ifr_name ) - 1 );

        if( ioctl( dev->fd_in, SIOCGIFINDEX, &ifr ) < 0 )
        {
            printf("Interface %s: \n", wi_get_ifname(wi));
            perror( "ioctl(SIOCGIFINDEX) failed" );
            return( 1 );
        }


        ifr.ifr_flags = 0;

        if( ioctl( dev->fd_in, SIOCSIFFLAGS, &ifr ) < 0 )
        {
            perror( "ioctl(SIOCSIFFLAGS) failed" );
            return( 1 );
        }

        usleep(100000);

        snprintf( s,  sizeof( s ) - 1, "%.1fM", (rate/1000000.0) );

        if( ( pid = fork() ) == 0 )
        {
            close( 0 ); close( 1 ); close( 2 ); unused = chdir( "/" );
            execlp(dev->iwconfig, "iwconfig", wi_get_ifname(wi),
                    "rate", s, NULL );
            exit( 1 );
        }

        waitpid( pid, &status, 0 );

        return 0;
        break;

    case DT_MAC80211_RT:

        dev->rate = (rate/500000);
        return 0;
        break;

    default:
        break;

    }


    memset( &wrq, 0, sizeof( struct iwreq ) );

    if(dev->main_if)
        strncpy( wrq.ifr_name, dev->main_if, IFNAMSIZ );
    else
        strncpy( wrq.ifr_name, wi_get_ifname(wi), IFNAMSIZ );

    wrq.u.bitrate.value = rate;
    if( ioctl( dev->fd_in, SIOCSIWRATE, &wrq ) < 0 )
    {
        return( -1 );
    }

    return 0;
}
