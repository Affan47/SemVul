sdbm_deletekey(DBM *db)
{
	if G_UNLIKELY(db == NULL) {
		errno = EINVAL;
		return -1;
	}
	sdbm_check(db);
	if G_UNLIKELY(db->flags & DBM_RDONLY) {
		errno = EPERM;
		return -1;
	}
	if G_UNLIKELY(db->flags & DBM_IOERR_W) {
		errno = EIO;
		return -1;
	}
	if G_UNLIKELY(db->flags & DBM_BROKEN) {
		errno = ESTALE;
		return -1;
	}


	if G_UNLIKELY(!(db->flags & DBM_ITERATING)) {
		g_critical("%s() called outside of any key iteration over SDBM \"%s\"",
			G_STRFUNC, sdbm_name(db));
		goto no_entry;
	}

	g_assert(db->pagbno == db->blkptr);

	if G_UNLIKELY(0 == db->keyptr)
		goto no_entry;

	if G_UNLIKELY(!delnpair(db, db->pagbuf, db->keyptr))
		return -1;

	db->keyptr--;


	if G_UNLIKELY(!flush_pagbuf(db))
		return -1;

	return 0;

no_entry:
	errno = ENOENT;
	return -1;
}
