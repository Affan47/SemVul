Cns_update_group_entry(dbfd, rec_addr, group_entry)
struct Cns_dbfd *dbfd;
Cns_dbrec_addr *rec_addr;
struct Cns_groupinfo *group_entry;
{
	char func[23];
	PGresult *res;
	char sql_stmt[1024];
	static char update_stmt[] =
		"UPDATE Cns_groupinfo SET GROUPNAME = '%s', BANNED = %d WHERE ROWID = %s";

	strcpy (func, "Cns_update_group_entry");
	sprintf (sql_stmt, update_stmt, group_entry->groupname, group_entry->banned,
	    *rec_addr);

	res = PQexec (dbfd->Pconn, sql_stmt);
	if (PQresultStatus (res) != PGRES_COMMAND_OK) {
		if (strstr (PQresultErrorMessage (res), "duplicate")) {
			serrno = EEXIST;
			PQclear (res);
		} else
			Cns_libpq_error (func, "UPDATE", res, dbfd);
		return (-1);
	}
	PQclear (res);
	return (0);
}
