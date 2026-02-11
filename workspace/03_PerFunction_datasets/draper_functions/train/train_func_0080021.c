check_header_hash(struct tdb_context *tdb,
			      uint32_t *m1, uint32_t *m2)
{
	if (hash_correct(tdb, m1, m2))
		return true;


	if (tdb->hash_fn == tdb1_old_hash)
		tdb->hash_fn = tdb1_incompatible_hash;
	else if (tdb->hash_fn == tdb1_incompatible_hash)
		tdb->hash_fn = tdb1_old_hash;
	else
		return false;
	return hash_correct(tdb, m1, m2);
}
