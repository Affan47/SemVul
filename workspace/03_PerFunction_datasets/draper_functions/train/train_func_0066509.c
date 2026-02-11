spam_sha1_add(const struct sha1 *sha1)
{
	g_assert(sha1_lut.state != SPAM_UNINITIALIZED);
	g_return_if_fail(sha1);

	if (sha1_lut.tab)
		sorted_array_add(sha1_lut.tab, sha1);
	else {
		if (SPAM_LOADING == sha1_lut.state) {
			dbmap_datum_t val = { NULL, 0 };
			dbmap_insert(sha1_lut.d.dm, sha1, val);
		} else {
			dbmw_write(sha1_lut.d.dw, sha1, NULL, 0);
		}
	}
}
