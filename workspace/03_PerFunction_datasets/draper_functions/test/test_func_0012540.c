tdb_recovery_size(struct tdb_context *tdb)
{
	tdb_len_t recovery_size = 0;
	int i;

	recovery_size = 0;
	for (i=0;i<tdb->tdb2.transaction->num_blocks;i++) {
		if (i * PAGESIZE >= tdb->tdb2.transaction->old_map_size) {
			break;
		}
		if (tdb->tdb2.transaction->blocks[i] == NULL) {
			continue;
		}
		recovery_size += 2*sizeof(tdb_off_t);
		if (i == tdb->tdb2.transaction->num_blocks-1) {
			recovery_size += tdb->tdb2.transaction->last_block_size;
		} else {
			recovery_size += PAGESIZE;
		}
	}

	return recovery_size;
}
