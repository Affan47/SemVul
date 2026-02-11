resolve_deltas(git_indexer *idx, git_transfer_progress *stats)
{
	unsigned int i;
	struct delta_info *delta;
	int progressed = 0, non_null = 0, progress_cb_result;

	while (idx->deltas.length > 0) {
		progressed = 0;
		non_null = 0;
		git_vector_foreach(&idx->deltas, i, delta) {
			git_rawobj obj;

			if (!delta)
				continue;

			non_null = 1;
			idx->off = delta->delta_off;
			if (git_packfile_unpack(&obj, idx->pack, &idx->off) < 0)
				continue;

			if (hash_and_save(idx, &obj, delta->delta_off) < 0)
				continue;

			git__free(obj.data);
			stats->indexed_objects++;
			stats->indexed_deltas++;
			progressed = 1;
			if ((progress_cb_result = do_progress_callback(idx, stats)) < 0)
				return progress_cb_result;


			git_vector_set(NULL, &idx->deltas, i, NULL);
			git__free(delta);
		}


		if (!non_null)
			break;

		if (!progressed && (fix_thin_pack(idx, stats) < 0)) {
			giterr_set(GITERR_INDEXER, "missing delta bases");
			return -1;
		}
	}

	return 0;
}
