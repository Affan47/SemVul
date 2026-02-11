tdb_find_zero_off(struct tdb_context *tdb, tdb_off_t off,
			   uint64_t num)
{
	uint64_t i;
	const uint64_t *val;


	val = tdb_access_read(tdb, off, num * sizeof(tdb_off_t), false);
	if (TDB_PTR_IS_ERR(val)) {
		return TDB_ERR_TO_OFF(TDB_PTR_ERR(val));
	}

	for (i = 0; i < num; i++) {
		if (!val[i])
			break;
	}
	tdb_access_release(tdb, val);
	return i;
}
