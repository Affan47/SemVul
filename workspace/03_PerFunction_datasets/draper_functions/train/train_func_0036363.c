dpm_insert_gfr_entry(dbfd, gfr_entry)
struct dpm_dbfd *dbfd;
struct dpm_get_filereq *gfr_entry;
{
	char escaped_ftype[3];
	char escaped_msg[255*2+1];
	char escaped_name[CA_MAXSFNLEN*2+1];
	char escaped_name2[CA_MAXSFNLEN*2+1];
	char escaped_protocol[CA_MAXPROTOLEN*2+1];
	char escaped_retpolicy[3];
	char escaped_server[CA_MAXHOSTNAMELEN*2+1];
	char escaped_token[CA_MAXDPMTOKENLEN*2+1];
	char escaped_token2[CA_MAXDPMTOKENLEN*2+1];
	char filesize_str[21];
	char func[21];
	static char insert_stmt[] =
		"INSERT INTO dpm_get_filereq \
		(R_TOKEN, F_ORDINAL, R_UID, FROM_SURL, \
		 PROTOCOL, LIFETIME, F_TYPE, S_TOKEN, \
		 RET_POLICY, FLAGS, SERVER, PFN, \
		 ACTUAL_SIZE, STATUS, ERRSTRING) \
		VALUES \
		('%s', %d, %d, '%s', '%s', %d, '%s', '%s', '%s', %d, '%s', '%s', %s, %d, '%s')";
	char sql_stmt[8192];

	strcpy (func, "dpm_insert_gfr_entry");
	dm_escape_string (&dbfd->mysql, escaped_msg, gfr_entry->errstring,
	    strlen (gfr_entry->errstring), sizeof(escaped_msg));
	dm_escape_string (&dbfd->mysql, escaped_ftype,
	    &gfr_entry->f_type, 1, sizeof(escaped_ftype));
	dm_escape_string (&dbfd->mysql, escaped_name, gfr_entry->from_surl,
	    strlen (gfr_entry->from_surl), sizeof(escaped_name));
	dm_escape_string (&dbfd->mysql, escaped_name2, gfr_entry->pfn,
	    strlen (gfr_entry->pfn), sizeof(escaped_name2));
	dm_escape_string (&dbfd->mysql, escaped_protocol, gfr_entry->protocol,
	    strlen (gfr_entry->protocol), sizeof(escaped_protocol));
	dm_escape_string (&dbfd->mysql, escaped_retpolicy,
	    &gfr_entry->ret_policy, 1, sizeof(escaped_retpolicy));
	dm_escape_string (&dbfd->mysql, escaped_token, gfr_entry->r_token,
	    strlen (gfr_entry->r_token), sizeof(escaped_token));
	dm_escape_string (&dbfd->mysql, escaped_token2, gfr_entry->s_token,
	    strlen (gfr_entry->s_token), sizeof(escaped_token2));
	dm_escape_string (&dbfd->mysql, escaped_server, gfr_entry->server,
	    strlen (gfr_entry->server), sizeof(escaped_server));
	dm_snprintf (sql_stmt, sizeof(sql_stmt), insert_stmt,
	    escaped_token, gfr_entry->f_ordinal, gfr_entry->r_uid,
	    escaped_name, escaped_protocol, gfr_entry->lifetime,
	    escaped_ftype, escaped_token2, escaped_retpolicy,
	    gfr_entry->flags, escaped_server, escaped_name2,
	    u64tostr (gfr_entry->actual_size, filesize_str, -1),
	    gfr_entry->status, escaped_msg);

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
