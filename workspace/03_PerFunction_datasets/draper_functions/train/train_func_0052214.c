getCopyResult(PGconn *conn, ExecStatusType copytype)
{


	if (conn->status != CONNECTION_OK)
	{
		pqSaveErrorResult(conn);
		conn->asyncStatus = PGASYNC_IDLE;
		return pqPrepareAsyncResult(conn);
	}


	if (conn->result && conn->result->resultStatus == copytype)
		return pqPrepareAsyncResult(conn);


	return PQmakeEmptyPGresult(conn, copytype);
}
