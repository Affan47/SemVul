PQexecFinish(PGconn *conn)
{
	PGresult   *result;
	PGresult   *lastResult;


	lastResult = NULL;
	while ((result = PQgetResult(conn)) != NULL)
	{
		if (lastResult)
		{
			if (lastResult->resultStatus == PGRES_FATAL_ERROR &&
				result->resultStatus == PGRES_FATAL_ERROR)
			{
				pqCatenateResultError(lastResult, result->errMsg);
				PQclear(result);
				result = lastResult;


				resetPQExpBuffer(&conn->errorMessage);
				appendPQExpBufferStr(&conn->errorMessage, result->errMsg);
			}
			else
				PQclear(lastResult);
		}
		lastResult = result;
		if (result->resultStatus == PGRES_COPY_IN ||
			result->resultStatus == PGRES_COPY_OUT ||
			conn->status == CONNECTION_BAD)
			break;
	}

	return lastResult;
}
