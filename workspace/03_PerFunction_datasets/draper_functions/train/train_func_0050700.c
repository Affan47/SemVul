dpm_decode_fs_entry(res, row, lock, rec_addr, fs_entry)
PGresult *res;
int row;
int lock;
dpm_dbrec_addr *rec_addr;
struct dpm_fs *fs_entry;
{
	int i = 0;

	if (lock)
		strcpy (*rec_addr, PQgetvalue (res, row, i++));
	strcpy (fs_entry->poolname, PQgetvalue (res, row, i++));
	strcpy (fs_entry->server, PQgetvalue (res, row, i++));
	strcpy (fs_entry->fs, PQgetvalue (res, row, i++));
	fs_entry->status = atoi (PQgetvalue (res, row, i++));
	fs_entry->weight = atoi (PQgetvalue (res, row, i));
}
