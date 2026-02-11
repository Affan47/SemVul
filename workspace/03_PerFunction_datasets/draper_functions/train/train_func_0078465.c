check_updates(struct unpack_trees_options *o)
{
	unsigned cnt = 0, total = 0;
	struct progress *progress = NULL;
	struct index_state *index = &o->result;
	int i;
	int errs = 0;

	if (o->update && o->verbose_update) {
		for (total = cnt = 0; cnt < index->cache_nr; cnt++) {
			struct cache_entry *ce = index->cache[cnt];
			if (ce->ce_flags & (CE_UPDATE | CE_REMOVE))
				total++;
		}

		progress = start_progress_delay("Checking out files",
						total, 50, 1);
		cnt = 0;
	}

	for (i = 0; i < index->cache_nr; i++) {
		struct cache_entry *ce = index->cache[i];

		if (ce->ce_flags & CE_REMOVE) {
			display_progress(progress, ++cnt);
			if (o->update)
				unlink_entry(ce);
			remove_index_entry_at(&o->result, i);
			i--;
			continue;
		}
	}

	for (i = 0; i < index->cache_nr; i++) {
		struct cache_entry *ce = index->cache[i];

		if (ce->ce_flags & CE_UPDATE) {
			display_progress(progress, ++cnt);
			ce->ce_flags &= ~CE_UPDATE;
			if (o->update) {
				errs |= checkout_entry(ce, &state, NULL);
			}
		}
	}
	stop_progress(&progress);
	return errs != 0;
}
