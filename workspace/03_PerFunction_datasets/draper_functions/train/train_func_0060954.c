Cns_update_class_entry(dbfd, rec_addr, class_entry)
struct Cns_dbfd *dbfd;
Cns_dbrec_addr *rec_addr;
struct Cns_class_metadata *class_entry;
{
	char func[23];
	PGresult *res;
	char sql_stmt[1024];
	static char update_stmt[] =
		"UPDATE Cns_class_metadata SET \
		NAME = '%s', OWNER_UID = %d, GID = %d, MIN_FILESIZE = %d, \
		MAX_FILESIZE = %d, FLAGS = %d, MAXDRIVES = %d, \
		MAX_SEGSIZE = %d, MIGR_TIME_INTERVAL = %d, \
		MINTIME_BEFOREMIGR = %d, NBCOPIES = %d, \
		NBDIRS_USING_CLASS = %d, RETENP_ON_DISK = %d \
		WHERE ROWID = %s";

	strcpy (func, "Cns_update_class_entry");
	sprintf (sql_stmt, update_stmt,
	    class_entry->name, class_entry->uid, class_entry->gid,
	    class_entry->min_filesize, class_entry->max_filesize,
	    class_entry->flags, class_entry->maxdrives,
	    class_entry->max_segsize, class_entry->migr_time_interval,
	    class_entry->mintime_beforemigr, class_entry->nbcopies,
	    class_entry->nbdirs_using_class, class_entry->retenp_on_disk,
	    *rec_addr);

	res = PQexec (dbfd->Pconn, sql_stmt);
	if (PQresultStatus (res) != PGRES_COMMAND_OK) {
		Cns_libpq_error (func, "UPDATE", res, dbfd);
		return (-1);
	}
	PQclear (res);
	return (0);
}
