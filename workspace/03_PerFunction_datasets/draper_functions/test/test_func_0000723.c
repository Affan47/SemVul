PQsendQuery(PGconn *conn, const char *query)
{
	if (!PQsendQueryStart(conn))
		return 0;

	if (!query)
	{
		printfPQExpBuffer(&conn->errorMessage,
						libpq_gettext("command string is a null pointer\n"));
		return 0;
	}


	if (pqPutMsgStart('Q', false, conn) < 0 ||
		pqPuts(query, conn) < 0 ||
		pqPutMsgEnd(conn) < 0)
	{
		pqHandleSendFailure(conn);
		return 0;
	}


	conn->queryclass = PGQUERY_SIMPLE;


	if (conn->last_query)
		free(conn->last_query);
	conn->last_query = strdup(query);


	if (pqFlush(conn) < 0)
	{
		pqHandleSendFailure(conn);
		return 0;
	}


	conn->asyncStatus = PGASYNC_BUSY;
	return 1;
}
