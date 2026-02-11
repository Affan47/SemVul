tdb_unlock_record(struct tdb_context *tdb, tdb_off_t off)
{
	struct tdb_traverse_lock *i;
	u32 count = 0;

	if (off == 0)
		return 0;
	for (i = &tdb->travlocks; i; i = i->next)
		if (i->off == off)
			count++;
	return (count == 1 ? tdb->methods->tdb_brlock(tdb, off, F_UNLCK, F_SETLKW, 0, 1) : 0);
}
