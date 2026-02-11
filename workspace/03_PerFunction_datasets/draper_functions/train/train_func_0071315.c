sdbm_close(DBM *db)
{
	bool clearfiles;

	if G_UNLIKELY(db == NULL)
		return;

	sdbm_check(db);

#ifdef LRU
	clearfiles = db->is_volatile;
#else
	clearfiles = FALSE;
#endif

	sdbm_close_internal(db, clearfiles, TRUE);
}
