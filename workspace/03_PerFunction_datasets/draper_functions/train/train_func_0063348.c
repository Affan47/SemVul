pdata_free(pdata_t *db)
{
	bool is_embedded;

	pdata_check(db);
	g_assert(0 == db->d_refcnt);

	is_embedded = (db->d_arena == db->d_embedded);


	if (db->d_free) {
		void *p = is_embedded ? (void *) db : (void *) db->d_arena;
		(*db->d_free)(p, db->d_arg);
		if (!is_embedded) {
			db->magic = 0;
			WFREE(db);
		}
	} else {
		size_t len = pdata_len(db);
		db->magic = 0;
		if (!is_embedded) {
			wfree(db->d_arena, len);
			WFREE(db);
		} else {
			wfree(db, len + EMBEDDED_OFFSET);
		}
	}
}
