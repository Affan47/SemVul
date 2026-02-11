makeEmptyPGconn(void)
{
	PGconn	   *conn;

#ifdef WIN32


	WSADATA		wsaData;

	if (WSAStartup(MAKEWORD(1, 1), &wsaData))
		return NULL;
	WSASetLastError(0);
#endif

	conn = (PGconn *) malloc(sizeof(PGconn));
	if (conn == NULL)
	{
#ifdef WIN32
		WSACleanup();
#endif
		return conn;
	}


	MemSet(conn, 0, sizeof(PGconn));

	conn->noticeHooks.noticeRec = defaultNoticeReceiver;
	conn->noticeHooks.noticeProc = defaultNoticeProcessor;
	conn->status = CONNECTION_BAD;
	conn->asyncStatus = PGASYNC_IDLE;
	conn->xactStatus = PQTRANS_IDLE;
	conn->options_valid = false;
	conn->nonblocking = false;
	conn->setenv_state = SETENV_STATE_IDLE;
	conn->client_encoding = PG_SQL_ASCII;
	conn->std_strings = false;
	conn->verbosity = PQERRORS_DEFAULT;
	conn->sock = -1;
	conn->auth_req_received = false;
	conn->password_needed = false;
	conn->dot_pgpass_used = false;
#ifdef USE_SSL
	conn->allow_ssl_try = true;
	conn->wait_ssl_try = false;
#endif


	conn->inBufSize = 16 * 1024;
	conn->inBuffer = (char *) malloc(conn->inBufSize);
	conn->outBufSize = 16 * 1024;
	conn->outBuffer = (char *) malloc(conn->outBufSize);
	initPQExpBuffer(&conn->errorMessage);
	initPQExpBuffer(&conn->workBuffer);

	if (conn->inBuffer == NULL ||
		conn->outBuffer == NULL ||
		PQExpBufferBroken(&conn->errorMessage) ||
		PQExpBufferBroken(&conn->workBuffer))
	{

		freePGconn(conn);
		conn = NULL;
	}

	return conn;
}
