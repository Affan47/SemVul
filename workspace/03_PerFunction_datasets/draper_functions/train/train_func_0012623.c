dpm_insert_pending_entry(dbfd, dpm_req)
struct dpm_dbfd *dbfd;
struct dpm_req *dpm_req;
{
	char escaped_groups[255*2+1];
	char escaped_host[CA_MAXHOSTNAMELEN*2+1];
	char escaped_msg[255*2+1];
	char escaped_name[255*2+1];
	char escaped_rtype[3];
	char escaped_token[CA_MAXDPMTOKENLEN*2+1];
	char escaped_utoken[255*2+1];
	char func[25];
	static char insert_stmt[] =
		"INSERT INTO dpm_pending_req \
		(R_ORDINAL, R_TOKEN, R_UID, \
		 R_GID, CLIENT_DN, CLIENTHOST, \
		 R_TYPE, U_TOKEN, \
		 FLAGS, RETRYTIME, NBREQFILES, \
		 CTIME, STIME, ETIME, \
		 STATUS, ERRSTRING, GROUPS) \
		VALUES \
		(%d, '%s', %d, %d, '%s', '%s', '%s', '%s', %d, %d, %d, %d, %d, %d, %d, '%s', '%s')";
	char sql_stmt[4096];

	strcpy (func, "dpm_insert_pending_entry");
	dm_escape_string (&dbfd->mysql, escaped_msg, dpm_req->errstring,
	    strlen (dpm_req->errstring), sizeof(escaped_msg));
	dm_escape_string (&dbfd->mysql, escaped_groups,
	    dpm_req->groups, strlen (dpm_req->groups), sizeof(escaped_groups));
	dm_escape_string (&dbfd->mysql, escaped_host, dpm_req->clienthost,
	    strlen (dpm_req->clienthost), sizeof(escaped_host));
	dm_escape_string (&dbfd->mysql, escaped_name, dpm_req->client_dn,
	    strlen (dpm_req->client_dn), sizeof(escaped_name));
	dm_escape_string (&dbfd->mysql, escaped_rtype,
	    &dpm_req->r_type, 1, sizeof(escaped_rtype));
	dm_escape_string (&dbfd->mysql, escaped_token, dpm_req->r_token,
	    strlen (dpm_req->r_token), sizeof(escaped_token));
	dm_escape_string (&dbfd->mysql, escaped_utoken, dpm_req->u_token,
	    strlen (dpm_req->u_token), sizeof(escaped_utoken));
	dm_snprintf (sql_stmt, sizeof(sql_stmt), insert_stmt,
	    dpm_req->r_ordinal, escaped_token, dpm_req->r_uid,
	    dpm_req->r_gid, escaped_name, escaped_host,
	    escaped_rtype, escaped_utoken,
	    dpm_req->flags, dpm_req->retrytime, dpm_req->nbreqfiles,
	    dpm_req->ctime, dpm_req->stime, dpm_req->etime,
	    dpm_req->status, escaped_msg, escaped_groups);

	if (dm_mysql_query (&dbfd->mysql, sql_stmt)) {
		if (mysql_errno (&dbfd->mysql) == ER_DUP_ENTRY)
			serrno = EEXIST;
		else {
			dpm_mysql_error (func, "INSERT", dbfd);
		}
		return (-1);
	}
	return (0);
}
