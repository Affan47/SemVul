main( int argc, char *argv[] )
{
        struct client_ctx ctx;
        struct sctp_event_subscribe event;
        int ret, domain;

        memset( &ctx, 0, sizeof( ctx));

        ctx.chunk_size = DEFAULT_CHUNK_SIZE;
        ctx.chunk_count = DEFAULT_COUNT;
        ctx.streamno = DEFAULT_STREAM_NO;
        ctx.ppid = DEFAULT_PPID;
        ctx.common.sock = -1;
        strncpy( ctx.filename, DEFAULT_FILENAME, FILENAME_LEN );

        ret =  parse_args(argc, argv, &ctx );
        if ( ret < 0 ) {
                WARN("Error while parsing args\n");
                return EXIT_FAILURE;
        } else if ( ret == 0 ) {
                return EXIT_SUCCESS;
        }


        if ( ctx.host.ss_family == AF_INET ) {
                ((struct sockaddr_in *)&(ctx.host))->sin_port = htons(ctx.port);
                domain = PF_INET;
        } else {
                ((struct sockaddr_in6 *)&(ctx.host))->sin6_port = htons(ctx.port);
                domain = PF_INET6;
        }
        if (common_init(&ctx.common) != 0)
                goto out;

        if (ctx.lport != 0 ) {
                if (bind_to_local_port(domain, ctx.common.sock, ctx.lport) != 0 ) {
                        close(ctx.common.sock);
                        return EXIT_FAILURE;
                }
        }

        if (is_flag(ctx.common.options, (VERBOSE_FLAG|ECHO_FLAG))) {


                memset(&event, 0, sizeof(event));
                event.sctp_data_io_event = 1;

                if (setsockopt(ctx.common.sock, IPPROTO_SCTP, SCTP_EVENTS,
                                        &event, sizeof(event)) != 0 ) {
                        WARN("Unable to register for SCTP IO events: %s \n",
                                        strerror(errno));

                }
        }

        do_client( &ctx );
out :
        common_deinit(&ctx.common);
        return EXIT_SUCCESS;
}
