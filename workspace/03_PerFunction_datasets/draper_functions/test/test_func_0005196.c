init_remote(CLI *c) {

    if(c->opt->option.local)
        c->bind_addr=&c->opt->source_addr;
#ifndef USE_WIN32
    else if(c->opt->option.transparent_src)
        c->bind_addr=&c->peer_addr;
#endif
    else
        c->bind_addr=NULL;


    if(c->opt->option.remote
#ifndef USE_WIN32
                || c->opt->option.transparent_dst
#endif
            ) {

        c->remote_fd.fd=connect_remote(c);
    } else if(c->opt->option.program) {
        c->remote_fd.fd=connect_local(c);
    } else {
        s_log(LOG_ERR, "INTERNAL ERROR: No target for remote socket");
        longjmp(c->err, 1);
    }

    c->remote_fd.is_socket=1;
    s_log(LOG_DEBUG, "Remote socket (FD=%d) initialized", c->remote_fd.fd);
    if(set_socket_options(c->remote_fd.fd, 2))
        s_log(LOG_WARNING, "Failed to set remote socket options");
}
