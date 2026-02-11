do_accept( struct server_ctx *ctx, struct sockaddr_storage *remote_ss,
                socklen_t *addrlen )
{
        int cli_fd = 0, ret = 0;
        fd_set fds;
        struct timeval tv;

        while( ret == 0 ) {
                if ( close_req )
                        return 0;

                FD_ZERO( &fds );
                FD_SET( ctx->common.sock, &fds );

                memset( &tv, 0, sizeof(tv));

                tv.tv_usec = ACCEPT_TIMEOUT_MS * 1000;

                ret = select( ctx->common.sock+1, &fds, NULL, NULL, &tv );
                if ( ret > 0 && FD_ISSET( ctx->common.sock, &fds ) )  {
                        TRACE("Going to accept()\n");
                        cli_fd = accept( ctx->common.sock, (struct sockaddr *)remote_ss,
                                        addrlen );
                        if ( cli_fd < 0 ) {
                                if ( errno == EINTR )
                                        continue;

                                print_error( "Error in accept()", errno);
#ifdef IGNORE_ACCEPT_ERROR
                                ret = 0;
                                continue;
#else
                                return -1;
#endif
                        }
                } else if ( ret < 0 ) {
                        if ( errno == EINTR )
                                continue;

                        print_error( "Error in select()", errno);
                        return -1;
                }
        }
        return cli_fd;
}
