loop(krb5_context context,
     krb5_kdc_configuration *config)
{
    struct descr *d;
    unsigned int ndescr;

    ndescr = init_sockets(context, config, &d);
    if(ndescr <= 0)
	krb5_errx(context, 1, "No sockets!");
    kdc_log(context, config, 0, "KDC started");
    while(exit_flag == 0){
	struct timeval tmout;
	fd_set fds;
	int min_free = -1;
	int max_fd = 0;
	size_t i;

	FD_ZERO(&fds);
	for(i = 0; i < ndescr; i++) {
	    if(!rk_IS_BAD_SOCKET(d[i].s)){
		if(d[i].type == SOCK_STREAM &&
		   d[i].timeout && d[i].timeout < time(NULL)) {
		    kdc_log(context, config, 1,
			    "TCP-connection from %s expired after %lu bytes",
			    d[i].addr_string, (unsigned long)d[i].len);
		    clear_descr(&d[i]);
		    continue;
		}
#ifndef NO_LIMIT_FD_SETSIZE
		if(max_fd < d[i].s)
		    max_fd = d[i].s;
#ifdef FD_SETSIZE
		if (max_fd >= FD_SETSIZE)
		    krb5_errx(context, 1, "fd too large");
#endif
#endif
		FD_SET(d[i].s, &fds);
	    }
	}

	tmout.tv_sec = TCP_TIMEOUT;
	tmout.tv_usec = 0;
	switch(select(max_fd + 1, &fds, 0, 0, &tmout)){
	case 0:
	    break;
	case -1:
	    if (errno != EINTR)
		krb5_warn(context, rk_SOCK_ERRNO, "select");
	    break;
	default:
	    for(i = 0; i < ndescr; i++)
		if(!rk_IS_BAD_SOCKET(d[i].s) && FD_ISSET(d[i].s, &fds)) {
            min_free = next_min_free(context, &d, &ndescr);

            if(d[i].type == SOCK_DGRAM)
                handle_udp(context, config, &d[i]);
            else if(d[i].type == SOCK_STREAM)
                handle_tcp(context, config, d, i, min_free);
		}
	}
    }
    if (0);
#ifdef SIGXCPU
    else if(exit_flag == SIGXCPU)
	kdc_log(context, config, 0, "CPU time limit exceeded");
#endif
    else if(exit_flag == SIGINT || exit_flag == SIGTERM)
	kdc_log(context, config, 0, "Terminated");
    else
	kdc_log(context, config, 0, "Unexpected exit reason: %d", exit_flag);
    free (d);
}
