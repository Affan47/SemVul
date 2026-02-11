gamt_connect(struct gamt_window *gamt)
{
    int rc;

    if (0 == strlen(amt_pass)) {
	char msg[128];

	snprintf(msg, sizeof(msg), "AMT password for %s@%s ?",
		 amt_user, amt_host);
	rc = gamt_getstring(gamt->win, "Authentication", msg,
			    amt_pass, sizeof(amt_pass), 1);
	if (0 != rc)
	    return -1;
    }

    memset(&gamt->redir, 0, sizeof(gamt->redir));
    memcpy(&gamt->redir.type, "SOL ", 4);

    snprintf(gamt->redir.host, sizeof(gamt->redir.host), "%s", amt_host);
    snprintf(gamt->redir.port, sizeof(gamt->redir.port), "%s", amt_port);
    snprintf(gamt->redir.user, sizeof(gamt->redir.user), "%s", amt_user);
    snprintf(gamt->redir.pass, sizeof(gamt->redir.pass), "%s", amt_pass);

    gamt->redir.verbose  = 1;
    gamt->redir.trace    = amt_trace;
    gamt->redir.cb_data  = gamt;
    gamt->redir.cb_recv  = recv_gtk;
    gamt->redir.cb_state = state_gtk;

    if (-1 == redir_connect(&gamt->redir))
	return -1;

    fcntl(gamt->redir.sock, F_SETFD, FD_CLOEXEC);
    vte_terminal_reset(VTE_TERMINAL(gamt->vte), TRUE, TRUE);
    gamt->ch = g_io_channel_unix_new(gamt->redir.sock);
    gamt->id = g_io_add_watch(gamt->ch, G_IO_IN, gamt_data, gamt);
    redir_start(&gamt->redir);
    return 0;
}
