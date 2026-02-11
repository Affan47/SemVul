tdb_allocate(struct tdb_context *tdb, tdb_len_t length, struct list_struct *rec)
{
	tdb_off_t rec_ptr, last_ptr, newrec_ptr;
	struct {
		tdb_off_t rec_ptr, last_ptr;
		tdb_len_t rec_len;
	} bestfit;

	if (tdb_lock(tdb, -1, F_WRLCK) == -1)
		return 0;


	length += sizeof(tdb_off_t);

 again:
	last_ptr = FREELIST_TOP;


	if (tdb_ofs_read(tdb, FREELIST_TOP, &rec_ptr) == -1)
		goto fail;

	bestfit.rec_ptr = 0;
	bestfit.last_ptr = 0;
	bestfit.rec_len = 0;


	while (rec_ptr) {
		if (tdb_rec_free_read(tdb, rec_ptr, rec) == -1) {
			goto fail;
		}

		if (rec->rec_len >= length) {
			if (bestfit.rec_ptr == 0 ||
			    rec->rec_len < bestfit.rec_len) {
				bestfit.rec_len = rec->rec_len;
				bestfit.rec_ptr = rec_ptr;
				bestfit.last_ptr = last_ptr;


				if (bestfit.rec_len < 2*length) {
					break;
				}
			}
		}


		last_ptr = rec_ptr;
		rec_ptr = rec->next;
	}

	if (bestfit.rec_ptr != 0) {
		if (tdb_rec_free_read(tdb, bestfit.rec_ptr, rec) == -1) {
			goto fail;
		}

		newrec_ptr = tdb_allocate_ofs(tdb, length, bestfit.rec_ptr, rec, bestfit.last_ptr);
		tdb_unlock(tdb, -1, F_WRLCK);
		return newrec_ptr;
	}


	if (tdb_expand(tdb, length + sizeof(*rec)) == 0)
		goto again;
 fail:
	tdb_unlock(tdb, -1, F_WRLCK);
	return 0;
}
