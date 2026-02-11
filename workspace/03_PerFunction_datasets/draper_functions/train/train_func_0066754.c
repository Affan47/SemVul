tdb1_dead_space(struct tdb_context *tdb, tdb1_off_t off)
{
	size_t len;

	for (len = 0; off + len < tdb->file->map_size; len++) {
		char c;
		if (tdb->tdb1.io->tdb1_read(tdb, off, &c, 1, 0))
			return 0;
		if (c != 0 && c != 0x42)
			break;
	}
	return len;
}
