PQputCopyData(PGconn *conn, const char *buffer, int nbytes)
{
	if (!conn)
		return -1;
	if (conn->asyncStatus != PGASYNC_COPY_IN)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("no COPY in progress\n"));
		return -1;
	}


	parseInput(conn);

	if (nbytes > 0)
	{


		if ((conn->outBufSize - conn->outCount - 5) < nbytes)
		{
			if (pqFlush(conn) < 0)
				return -1;
			if (pqCheckOutBufferSpace(conn->outCount + 5 + (size_t) nbytes,
									  conn))
				return pqIsnonblocking(conn) ? 0 : -1;
		}

		if (PG_PROTOCOL_MAJOR(conn->pversion) >= 3)
		{
			if (pqPutMsgStart('d', false, conn) < 0 ||
				pqPutnchar(buffer, nbytes, conn) < 0 ||
				pqPutMsgEnd(conn) < 0)
				return -1;
		}
		else
		{
			if (pqPutMsgStart(0, false, conn) < 0 ||
				pqPutnchar(buffer, nbytes, conn) < 0 ||
				pqPutMsgEnd(conn) < 0)
				return -1;
		}
	}
	return 1;
}
