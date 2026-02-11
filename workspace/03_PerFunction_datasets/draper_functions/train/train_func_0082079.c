fetch_dirbuf(DBM *db, long dirb)
{
	db->dirfetch++;

	if (dirb != db->dirbno) {
		ssize_t got;

#ifdef LRU
		if (db->dirbuf_dirty && !flush_dirbuf(db))
			return FALSE;
#endif

		db->dirread++;
		got = compat_pread(db->dirf, db->dirbuf, DBM_DBLKSIZ, OFF_DIR(dirb));
		if G_UNLIKELY(got < 0) {
			g_critical("sdbm: \"%s\": could not read dir page #%ld: %m",
				sdbm_name(db), dirb);
			ioerr(db, FALSE);
			return FALSE;
		}

		if G_UNLIKELY(0 == got) {
			memset(db->dirbuf, 0, DBM_DBLKSIZ);
		}
		db->dirbno = dirb;

		debug(("dir read: %ld\n", dirb));
	} else {
		db->dirbno_hit++;
	}
	return TRUE;
}
