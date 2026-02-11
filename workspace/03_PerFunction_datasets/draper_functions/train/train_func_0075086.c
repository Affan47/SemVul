add_route( char **args ) {

    struct rtentry route;
    int i = 1;
    int fd;

    create_route(&route, args);

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        return 0;


    ioctl( fd, SIOCDELRT, &route );
    if( ioctl( fd, SIOCADDRT, &route ) < 0) {
        i = 0;
    }

    close( fd );
    return i;
}
