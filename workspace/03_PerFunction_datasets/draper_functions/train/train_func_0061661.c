transaction_read(struct tdb_context *tdb, tdb_off_t off, void *buf,
			    tdb_len_t len, int cv)
{
	uint32_t blk;


	while (len + (off % tdb->transaction->block_size) > tdb->transaction->block_size) {
		tdb_len_t len2 = tdb->transaction->block_size - (off % tdb->transaction->block_size);
		if (transaction_read(tdb, off, buf, len2, cv) != 0) {
			return -1;
		}
		len -= len2;
		off += len2;
		buf = (void *)(len2 + (char *)buf);
	}

	if (len == 0) {
		return 0;
	}

	blk = off / tdb->transaction->block_size;


	if (tdb->transaction->num_blocks <= blk ||
	    tdb->transaction->blocks[blk] == NULL) {

		if (tdb->transaction->io_methods->tdb_read(tdb, off, buf, len, cv) != 0) {
			goto fail;
		}
		return 0;
	}


	if (blk == tdb->transaction->num_blocks-1) {
		if (len > tdb->transaction->last_block_size) {
			goto fail;
		}
	}


	memcpy(buf, tdb->transaction->blocks[blk] + (off % tdb->transaction->block_size), len);
	if (cv) {
		tdb_convert(buf, len);
	}
	return 0;

fail:
	TDB_LOG((tdb, TDB_DEBUG_FATAL, "transaction_read: failed at off=%d len=%d\n", off, len));
	tdb->ecode = TDB_ERR_IO;
	tdb->transaction->transaction_error = 1;
	return -1;
}
