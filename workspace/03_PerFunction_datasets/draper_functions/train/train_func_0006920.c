getRowDescriptions(PGconn *conn)
{
	PGresult   *result;
	int			nfields;
	int			i;


	if (conn->queryclass == PGQUERY_DESCRIBE)
	{
		if (conn->result)
			result = conn->result;
		else
			result = PQmakeEmptyPGresult(conn, PGRES_COMMAND_OK);
	}
	else
		result = PQmakeEmptyPGresult(conn, PGRES_TUPLES_OK);
	if (!result)
		goto failure;


	if (pqGetInt(&(result->numAttributes), 2, conn))
		goto failure;
	nfields = result->numAttributes;


	if (nfields > 0)
	{
		result->attDescs = (PGresAttDesc *)
			pqResultAlloc(result, nfields * sizeof(PGresAttDesc), TRUE);
		if (!result->attDescs)
			goto failure;
		MemSet(result->attDescs, 0, nfields * sizeof(PGresAttDesc));
	}


	result->binary = (nfields > 0) ? 1 : 0;


	for (i = 0; i < nfields; i++)
	{
		int			tableid;
		int			columnid;
		int			typid;
		int			typlen;
		int			atttypmod;
		int			format;

		if (pqGets(&conn->workBuffer, conn) ||
			pqGetInt(&tableid, 4, conn) ||
			pqGetInt(&columnid, 2, conn) ||
			pqGetInt(&typid, 4, conn) ||
			pqGetInt(&typlen, 2, conn) ||
			pqGetInt(&atttypmod, 4, conn) ||
			pqGetInt(&format, 2, conn))
		{
			goto failure;
		}


		columnid = (int) ((int16) columnid);
		typlen = (int) ((int16) typlen);
		format = (int) ((int16) format);

		result->attDescs[i].name = pqResultStrdup(result,
												  conn->workBuffer.data);
		if (!result->attDescs[i].name)
			goto failure;
		result->attDescs[i].tableid = tableid;
		result->attDescs[i].columnid = columnid;
		result->attDescs[i].format = format;
		result->attDescs[i].typid = typid;
		result->attDescs[i].typlen = typlen;
		result->attDescs[i].atttypmod = atttypmod;

		if (format != 1)
			result->binary = 0;
	}


	conn->result = result;
	return 0;

failure:


	if (result != conn->result)
		PQclear(result);
	return EOF;
}
