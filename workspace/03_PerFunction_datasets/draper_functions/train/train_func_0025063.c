PQsendQueryStart(PGconn *conn)
{
	if (!conn)
		return false;


	resetPQExpBuffer(&conn->errorMessage);


	if (conn->status != CONNECTION_OK)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("no connection to the server\n"));
		return false;
	}

	if (conn->asyncStatus != PGASYNC_IDLE)
	{
		printfPQExpBuffer(&conn->errorMessage,
				  libpq_gettext("another command is already in progress\n"));
		return false;
	}


	conn->result = NULL;
	conn->curTuple = NULL;


	return true;
}
