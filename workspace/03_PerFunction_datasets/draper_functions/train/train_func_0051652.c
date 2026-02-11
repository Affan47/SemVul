server_loop()
{
    size_t i;
    fd_set fdset;

    FD_ZERO(&fdset);
    for (i = 0; i < srvcount; i++)
	FD_SET(srvtab[i].fd, &fdset);

    for (;;) {
	int rc;
	fd_set rdset;

	if (need_cleanup) {
	    cleanup_children(0);
	    need_cleanup = 1;
	}

	if (num_children > max_children) {
	    dico_log(L_ERR, 0, _("too many children (%lu)"), num_children);
	    pause();
	    continue;
	}

	rdset = fdset;
	rc = select (fdmax + 1, &rdset, NULL, NULL, NULL);
	if (rc == -1 && errno == EINTR) {
	    if (stop)
		break;
	    else if (restart) {
		if (pre_restart_lint() == 0)
		    break;
		else
		    restart = 0;
	    }
	    continue;
	} else if (rc < 0) {
	    dico_log(L_CRIT, errno, _("select error"));
	    return EX_OSERR;
	}

	for (i = 0; i < srvcount; i++)
	    if (FD_ISSET(srvtab[i].fd, &rdset))
		handle_connection(i);
    }
    return 0;
}
