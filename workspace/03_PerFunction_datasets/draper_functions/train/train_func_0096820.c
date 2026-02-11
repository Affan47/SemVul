popd_reset(void)
{
    int bytes_in = 0;
    int bytes_out = 0;

    proc_cleanup();

    syslog(LOG_NOTICE, "counts: retr=<%d> top=<%d> dele=<%d>",
                       count_retr, count_top, count_dele);
    count_retr = 0;
    count_top = 0;
    count_dele = 0;


    if (popd_mailbox)
	mailbox_close(&popd_mailbox);


    if (backend) {
	backend_disconnect(backend);
	free(backend);
	backend = NULL;
    }

    if (popd_in) {
	prot_NONBLOCK(popd_in);
	prot_fill(popd_in);
	bytes_in = prot_bytes_in(popd_in);
	prot_free(popd_in);
    }

    if (popd_out) {
	prot_flush(popd_out);
	bytes_out = prot_bytes_out(popd_out);
	prot_free(popd_out);
    }

    if (config_auditlog)
	syslog(LOG_NOTICE, "auditlog: traffic sessionid=<%s> bytes_in=<%d> bytes_out=<%d>",
			   session_id(), bytes_in, bytes_out);

    popd_in = popd_out = NULL;

#ifdef HAVE_SSL
    if (tls_conn) {
	tls_reset_servertls(&tls_conn);
	tls_conn = NULL;
    }
#endif

    cyrus_reset_stdio();

    strcpy(popd_clienthost, "[local]");
    if (popd_logfd != -1) {
	close(popd_logfd);
	popd_logfd = -1;
    }
    if (popd_userid != NULL) {
	free(popd_userid);
	popd_userid = NULL;
    }
    if (popd_subfolder != NULL) {
	free(popd_subfolder);
	popd_subfolder = NULL;
    }
    if (popd_authstate) {
	auth_freestate(popd_authstate);
	popd_authstate = NULL;
    }
    if (popd_saslconn) {
	sasl_dispose(&popd_saslconn);
	popd_saslconn = NULL;
    }
    popd_starttls_done = 0;

    if(saslprops.iplocalport) {
       free(saslprops.iplocalport);
       saslprops.iplocalport = NULL;
    }
    if(saslprops.ipremoteport) {
       free(saslprops.ipremoteport);
       saslprops.ipremoteport = NULL;
    }
    if(saslprops.authid) {
       free(saslprops.authid);
       saslprops.authid = NULL;
    }
    saslprops.ssf = 0;

    popd_exists = 0;
}
