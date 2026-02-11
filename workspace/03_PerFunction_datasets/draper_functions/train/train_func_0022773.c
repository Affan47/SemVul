read_db(const char *name, long count, long cache, int wflags, tm_t *done)
{
	DBM *db = open_db(name, shrink ? TRUE : FALSE, cache, wflags);
	long i;
	char buf[1024];
	datum key;
	long cpage = 0 == cache ? 64 : cache;

	printf("Starting read test (%ld item%s), cache=%ld page%s...\n",
		count, 1 == count ? "" : "s", cpage, 1 == cpage ? "" : "s");

	key.dsize = large_keys ? sizeof buf : NORMAL_KEY_LEN;
	key.dptr = buf;

	for (i = 0; i < count; i++) {
		datum val;

		if (progress && 0 == i % 500)
			show_progress(i, count);

		fill_key(buf, sizeof buf, i);
		val = sdbm_fetch(db, key);
		if (NULL == val.dptr) {
			if (sdbm_error(db))
				oops("read error at item #%ld", i);
			oops("item #%ld not found", i);
		}
	}

	show_done(done);

	sdbm_close(db);
}
