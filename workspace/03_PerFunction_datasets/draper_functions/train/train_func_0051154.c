validpage(DBM *db, long pagb)
{
	int n;
	int i;
	char *pag = db->pagbuf;
	unsigned short *ino = (unsigned short *) pag;
	int removed = 0;
	int corrupted = 0;

	n = ino[0];

	for (i = n - 1; i > 0; i -= 2) {
		datum key;
		long int hash;
		long kpag;
		int k = (i + 1) / 2;

		key = getnkey(db, pag, k);
		hash = exhash(key);
		kpag = getpageb(db, hash, FALSE);

		if G_UNLIKELY(kpag != pagb) {
			if (delipair(db, pag, i, TRUE)) {
				removed++;
			} else {

				g_warning("sdbm: \"%s\": cannot remove key #%d/%d "
					"not belonging to page #%ld",
					sdbm_name(db), k, n / 2, pagb);
			}
		} else if G_UNLIKELY(!chkipair(db, pag, i)) {

			if (delipair(db, pag, i, FALSE)) {
				corrupted++;
			} else {
				g_warning("sdbm: \"%s\": cannot remove corrupted entry #%d/%d "
					"in page #%ld",
					sdbm_name(db), k, n / 2, pagb);
			}
		}
	}

	if G_UNLIKELY(removed > 0 || corrupted > 0) {
		if (removed > 0) {
			db->removed_keys += removed;
			g_warning("sdbm: \"%s\": removed %d/%d key%s "
				"not belonging to page #%ld", sdbm_name(db),
				removed, n / 2, 1 == removed ? "" : "s", pagb);
		}
		if (corrupted > 0) {
			db->removed_keys += corrupted;
			g_warning("sdbm: \"%s\": removed %d/%d corrupted entr%s "
				"on page #%ld", sdbm_name(db),
				corrupted, n / 2, 1 == corrupted ? "y" : "ies", pagb);
		}
#ifdef LRU
		(void) force_flush_pagbuf(db, !db->is_volatile);
#else
		(void) flush_pagbuf(db);
#endif
	}
}
