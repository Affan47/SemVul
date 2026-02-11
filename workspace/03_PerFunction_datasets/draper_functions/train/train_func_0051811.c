dcc_server_started(SERVER_DCC_REC *dcc)
{
	if (!IS_DCC_SERVER(dcc)) {
		return;
	}

	printformat(dcc->server, NULL, MSGLEVEL_DCC,
		    IRCTXT_DCC_SERVER_STARTED, dcc->port);
}
