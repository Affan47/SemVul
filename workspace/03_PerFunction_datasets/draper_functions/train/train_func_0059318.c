dpm_list_rr_puts(dbfd, bol, pfr_entry, endlist, dblistptr)
struct dpm_dbfd *dbfd;
int bol;
struct dpm_put_filereq *pfr_entry;
int endlist;
DBLISTPTR *dblistptr;
{
	char func[17];
	static char query[] =
		"SELECT \
		 R_TOKEN, F_ORDINAL, TO_SURL, PROTOCOL, \
		 LIFETIME, F_LIFETIME, F_TYPE, S_TOKEN, \
		 RET_POLICY, AC_LATENCY, REQUESTED_SIZE, \
		 SERVER, PFN, \
		 ACTUAL_SIZE, STATUS, ERRSTRING \
		FROM dpm_put_filereq \
		WHERE status = %d OR status = %d";
	PGresult *res;
	char sql_stmt[1024];

	strcpy (func, "dpm_list_rr_puts");
	if (endlist) {
		PQclear (dblistptr->res);
		return (1);
	}
	if (bol) {
		sprintf (sql_stmt, query, DPM_READY, DPM_RUNNING);
		res = PQexec (dbfd->Pconn, sql_stmt);
		if (PQresultStatus (res) != PGRES_TUPLES_OK) {
			dpm_libpq_error (func, "SELECT", res, dbfd);
			return (-1);
		}
		dblistptr->res = res;
		dblistptr->row = 0;
	}
	if (dblistptr->row >= PQntuples (dblistptr->res))
		return (1);
	dpm_decode_pfr_entry (dblistptr->res, dblistptr->row, 0, NULL, pfr_entry);
	dblistptr->row++;
	return (0);
}
