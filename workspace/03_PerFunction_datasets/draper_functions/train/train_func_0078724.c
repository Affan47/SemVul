sdbm_sync(DBM *db)
{
	ssize_t npag = 0;

	sdbm_check(db);

	if G_UNLIKELY(db->flags & DBM_BROKEN) {
		errno = ESTALE;
		return -1;
	}

#ifdef LRU
	npag = flush_dirtypag(db);
	if G_UNLIKELY(-1 == npag)
		return -1;

	if (db->dirbuf_dirty) {
		if G_UNLIKELY(!flush_dirbuf(db))
			return -1;
		npag++;
	}
#else
	(void) db;
#endif

#ifdef BIGDATA
	if (big_sync(db))
		npag++;
#endif

	return npag;
}
