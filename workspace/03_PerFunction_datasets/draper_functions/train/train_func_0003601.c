canRead ( unsigned int    sec,
                          unsigned int    usec )    throw ( Exception )
{
    fd_set              fdset;
    struct timeval      tv;
    int                 ret;

    if ( !isOpen() ) {
        return false;
    }

    FD_ZERO( &fdset);
    FD_SET( fileDescriptor, &fdset);
    tv.tv_sec  = sec;
    tv.tv_usec = usec;

    ret = select( fileDescriptor + 1, &fdset, NULL, NULL, &tv);

    if ( ret == -1 ) {
        throw Exception( __FILE__, __LINE__, "select error");
    }

    return ret > 0;
}
