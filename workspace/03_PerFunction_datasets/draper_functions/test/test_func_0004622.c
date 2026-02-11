client_proc( int sd )
{
    char buff[1024];
    memset( buff, 0, sizeof( buff ) );

    int res = 0;
    do{
        res = recv( sd, buff, sizeof( buff ), MSG_DONTWAIT );
        if( errno != EINTR ){
            break;
        }
    }while(true);

    if( res < 0 ){
        if( ( errno == EAGAIN ) ||
            ( errno == EWOULDBLOCK ) ){
            printf( "Not ready yet.\n" );
        }
        else{
            perror( "recv()" );
            FD_CLR( sd, &g_fds );
            close( sd );
            return;
        }
    }
    else if( res == 0 ){
        printf( "disconeccted. sd:%d\n", sd );
        FD_CLR( sd, &g_fds );
        close( sd );
        return;
    }

    printf( "received. sd:%d buff:%s\n", sd, buff );
}
