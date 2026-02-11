jdwp_control_init( JdwpControl*  control,
                   const char*   sockname,
                   int           socknamelen )
{
    struct sockaddr_un   addr;
    socklen_t            addrlen;
    int                  s;
    int                  maxpath = sizeof(addr.sun_path);
    int                  pathlen = socknamelen;

    if (pathlen >= maxpath) {
        D( "vm debug control socket name too long (%d extra chars)\n",
           pathlen+1-maxpath );
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    memcpy(addr.sun_path, sockname, socknamelen);

    s = socket( AF_UNIX, SOCK_STREAM, 0 );
    if (s < 0) {
        D( "could not create vm debug control socket. %d: %s\n",
           errno, strerror(errno));
        return -1;
    }

    addrlen = (pathlen + sizeof(addr.sun_family));

    if (bind(s, (struct sockaddr*)&addr, addrlen) < 0) {
        D( "could not bind vm debug control socket: %d: %s\n",
           errno, strerror(errno) );
        adb_close(s);
        return -1;
    }

    if ( listen(s, 4) < 0 ) {
        D("listen failed in jdwp control socket: %d: %s\n",
          errno, strerror(errno));
        adb_close(s);
        return -1;
    }

    control->listen_socket = s;

    control->fde = fdevent_create(s, jdwp_control_event, control);
    if (control->fde == NULL) {
        D( "could not create fdevent for jdwp control socket\n" );
        adb_close(s);
        return -1;
    }


    fdevent_add(control->fde, FDE_READ);
    close_on_exec(s);

    D("jdwp control socket started (%d)\n", control->listen_socket);
    return 0;
}
