Cns_insert_group_entry(dbfd, group_entry)
struct Cns_dbfd *dbfd;
struct Cns_groupinfo *group_entry;
{
	char escaped_name[255*2+1];
	char func[23];
	static char insert_stmt[] =
		"INSERT INTO Cns_groupinfo (GID, GROUPNAME, BANNED) VALUES (%d, '%s', %d)";
	char sql_stmt[1024];

	strcpy (func, "Cns_insert_group_entry");
	dm_escape_string (&dbfd->mysql, escaped_name, group_entry->groupname,
	    strlen (group_entry->groupname), sizeof(escaped_name));
	dm_snprintf (sql_stmt, sizeof(sql_stmt), insert_stmt, group_entry->gid,
	    escaped_name, group_entry->banned);
	if (mysql_query (&dbfd->mysql, sql_stmt)) {
		if (mysql_errno (&dbfd->mysql) == ER_DUP_ENTRY)
			serrno = EEXIST;
		else {
			Cns_mysql_error (func, "INSERT", dbfd);
		}
		return (-1);
	}
	return (0);
}
