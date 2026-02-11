Cns_insert_fmd_entry(dbfd, fmd_entry)
struct Cns_dbfd *dbfd;
struct Cns_file_metadata *fmd_entry;
{
	char escaped_name[CA_MAXNAMELEN*2+1];
	char fileid_str[21];
	char filesize_str[21];
	char func[21];
	static char insert_stmt[] =
		"INSERT INTO Cns_file_metadata \
		(FILEID, PARENT_FILEID, GUID, NAME, FILEMODE, NLINK, OWNER_UID, \
		 GID, FILESIZE, ATIME, MTIME, CTIME, FILECLASS, STATUS, CSUMTYPE, \
		 CSUMVALUE, ACL) \
		VALUES \
		(%s, %s, '%s', '%s', %d, %d, %d, %d, %s, %d, %d, %d, %d, '%c', '%s', '%s', '%s')";
	static char insert_stmt_null_guid[] =
		"INSERT INTO Cns_file_metadata \
		(FILEID, PARENT_FILEID, GUID, NAME, FILEMODE, NLINK, OWNER_UID, \
		 GID, FILESIZE, ATIME, MTIME, CTIME, FILECLASS, STATUS, CSUMTYPE, \
		 CSUMVALUE, ACL) \
		VALUES \
		(%s, %s, NULL, '%s', %d, %d, %d, %d, %s, %d, %d, %d, %d, '%c', '%s', '%s', '%s')";
	char parent_fileid_str[21];
	PGresult *res;
	char sql_stmt[1024];

	strcpy (func, "Cns_insert_fmd_entry");
	PQescapeStringConn (dbfd->Pconn, escaped_name, fmd_entry->name,
	    strlen (fmd_entry->name), NULL);
	if (*fmd_entry->guid)
		sprintf (sql_stmt, insert_stmt,
		    u64tostr (fmd_entry->fileid, fileid_str, -1),
		    u64tostr (fmd_entry->parent_fileid, parent_fileid_str, -1),
		    fmd_entry->guid, escaped_name, fmd_entry->filemode, fmd_entry->nlink,
		    fmd_entry->uid, fmd_entry->gid,
		    u64tostr (fmd_entry->filesize, filesize_str, -1),
		    (int)fmd_entry->atime, (int)fmd_entry->mtime, (int)fmd_entry->ctime,
		    fmd_entry->fileclass, fmd_entry->status, fmd_entry->csumtype,
		    fmd_entry->csumvalue, fmd_entry->acl);
	else

		sprintf (sql_stmt, insert_stmt_null_guid,
		    u64tostr (fmd_entry->fileid, fileid_str, -1),
		    u64tostr (fmd_entry->parent_fileid, parent_fileid_str, -1),
		    escaped_name, fmd_entry->filemode, fmd_entry->nlink,
		    fmd_entry->uid, fmd_entry->gid,
		    u64tostr (fmd_entry->filesize, filesize_str, -1),
		    (int)fmd_entry->atime, (int)fmd_entry->mtime, (int)fmd_entry->ctime,
		    fmd_entry->fileclass, fmd_entry->status, fmd_entry->csumtype,
		    fmd_entry->csumvalue, fmd_entry->acl);

	res = PQexec (dbfd->Pconn, sql_stmt);
	if (PQresultStatus (res) != PGRES_COMMAND_OK) {
		if (strstr (PQresultErrorMessage (res), "duplicate")) {
			serrno = EEXIST;
			PQclear (res);
		} else
			Cns_libpq_error (func, "INSERT", res, dbfd);
		return (-1);
	}
	PQclear (res);
	return (0);
}
