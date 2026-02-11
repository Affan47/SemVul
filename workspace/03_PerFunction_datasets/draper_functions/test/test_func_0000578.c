mydbm_close (DBM *db)
{
    if (db->modified)
    {
	FILE *fp;
	fp = CVS_FOPEN (db->name, FOPEN_BINARY_WRITE);
	if (fp == NULL)
	    error (1, errno, "cannot write %s", db->name);
	walklist (db->dbm_list, write_item, fp);
	if (fclose (fp) < 0)
	    error (0, errno, "cannot close %s", db->name);
    }
    free (db->name);
    dellist (&db->dbm_list);
    free (db);
}
