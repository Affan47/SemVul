libpqrcv_connect(char *conninfo, XLogRecPtr startpoint)
{
	char		conninfo_repl[MAXCONNINFO + 37];
	char	   *primary_sysid;
	char		standby_sysid[32];
	TimeLineID	primary_tli;
	TimeLineID	standby_tli;
	PGresult   *res;
	char		cmd[64];


	snprintf(conninfo_repl, sizeof(conninfo_repl),
			 "%s dbname=replication replication=true",
			 conninfo);

	streamConn = PQconnectdb(conninfo_repl);
	if (PQstatus(streamConn) != CONNECTION_OK)
		ereport(ERROR,
				(errmsg("could not connect to the primary server: %s",
						PQerrorMessage(streamConn))));


	res = libpqrcv_PQexec("IDENTIFY_SYSTEM");
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		PQclear(res);
		ereport(ERROR,
				(errmsg("could not receive database system identifier and timeline ID from "
						"the primary server: %s",
						PQerrorMessage(streamConn))));
	}
	if (PQnfields(res) != 2 || PQntuples(res) != 1)
	{
		int			ntuples = PQntuples(res);
		int			nfields = PQnfields(res);

		PQclear(res);
		ereport(ERROR,
				(errmsg("invalid response from primary server"),
				 errdetail("Expected 1 tuple with 2 fields, got %d tuples with %d fields.",
						   ntuples, nfields)));
	}
	primary_sysid = PQgetvalue(res, 0, 0);
	primary_tli = pg_atoi(PQgetvalue(res, 0, 1), 4, 0);


	snprintf(standby_sysid, sizeof(standby_sysid), UINT64_FORMAT,
			 GetSystemIdentifier());
	if (strcmp(primary_sysid, standby_sysid) != 0)
	{
		PQclear(res);
		ereport(ERROR,
				(errmsg("database system identifier differs between the primary and standby"),
				 errdetail("The primary's identifier is %s, the standby's identifier is %s.",
						   primary_sysid, standby_sysid)));
	}


	standby_tli = GetRecoveryTargetTLI();
	PQclear(res);
	if (primary_tli != standby_tli)
		ereport(ERROR,
				(errmsg("timeline %u of the primary does not match recovery target timeline %u",
						primary_tli, standby_tli)));
	ThisTimeLineID = primary_tli;


	snprintf(cmd, sizeof(cmd), "START_REPLICATION %X/%X",
			 startpoint.xlogid, startpoint.xrecoff);
	res = libpqrcv_PQexec(cmd);
	if (PQresultStatus(res) != PGRES_COPY_BOTH)
	{
		PQclear(res);
		ereport(ERROR,
				(errmsg("could not start WAL streaming: %s",
						PQerrorMessage(streamConn))));
	}
	PQclear(res);

	justconnected = true;
	ereport(LOG,
		(errmsg("streaming replication successfully connected to primary")));

	return true;
}
