PQendcopy(PGconn *conn)
{
	if (!conn)
		return 0;

	if (PG_PROTOCOL_MAJOR(conn->pversion) >= 3)
		return pqEndcopy3(conn);
	else
		return pqEndcopy2(conn);
}
