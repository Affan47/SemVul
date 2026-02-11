setup_remotetcp() {

	struct TCPFwdList * iter = NULL;

	TRACE(("enter setup_remotetcp"))

	if (cli_opts.remotefwds == NULL) {
		TRACE(("cli_opts.remotefwds == NULL"))
	}

	iter = cli_opts.remotefwds;

	while (iter != NULL) {
		send_msg_global_request_remotetcp(iter->listenport);
		iter = iter->next;
	}
	TRACE(("leave setup_remotetcp"))
}
