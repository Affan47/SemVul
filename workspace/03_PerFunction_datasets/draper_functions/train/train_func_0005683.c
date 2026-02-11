repack_worthwhile(struct tdb_context *tdb)
{
	tdb1_off_t ptr;
	struct tdb1_record rec;
	tdb1_len_t total = 0, largest = 0;

	if (tdb1_ofs_read(tdb, TDB1_FREELIST_TOP, &ptr) == -1) {
		return false;
	}

	while (ptr != 0 && tdb1_rec_free_read(tdb, ptr, &rec) == 0) {
		total += rec.rec_len;
		if (rec.rec_len > largest) {
			largest = rec.rec_len;
		}
		ptr = rec.next;
	}

	return total > largest * 2;
}
