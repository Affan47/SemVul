__origin_write(struct list_head *snapshots, sector_t sector,
			  struct bio *bio)
{
	int r = DM_MAPIO_REMAPPED;
	struct dm_snapshot *snap;
	struct dm_exception *e;
	struct dm_snap_pending_exception *pe;
	struct dm_snap_pending_exception *pe_to_start_now = NULL;
	struct dm_snap_pending_exception *pe_to_start_last = NULL;
	chunk_t chunk;


	list_for_each_entry (snap, snapshots, list) {


		if (dm_target_is_snapshot_merge(snap->ti))
			continue;

		down_write(&snap->lock);


		if (!snap->valid || !snap->active)
			goto next_snapshot;


		if (sector >= dm_table_get_size(snap->ti->table))
			goto next_snapshot;


		chunk = sector_to_chunk(snap->store, sector);


		e = dm_lookup_exception(&snap->complete, chunk);
		if (e)
			goto next_snapshot;

		pe = __lookup_pending_exception(snap, chunk);
		if (!pe) {
			up_write(&snap->lock);
			pe = alloc_pending_exception(snap);
			down_write(&snap->lock);

			if (!snap->valid) {
				free_pending_exception(pe);
				goto next_snapshot;
			}

			e = dm_lookup_exception(&snap->complete, chunk);
			if (e) {
				free_pending_exception(pe);
				goto next_snapshot;
			}

			pe = __find_pending_exception(snap, pe, chunk);
			if (!pe) {
				__invalidate_snapshot(snap, -ENOMEM);
				goto next_snapshot;
			}
		}

		r = DM_MAPIO_SUBMITTED;


		if (bio) {
			bio_list_add(&pe->origin_bios, bio);
			bio = NULL;

			if (!pe->started) {
				pe->started = 1;
				pe_to_start_last = pe;
			}
		}

		if (!pe->started) {
			pe->started = 1;
			pe_to_start_now = pe;
		}

next_snapshot:
		up_write(&snap->lock);

		if (pe_to_start_now) {
			start_copy(pe_to_start_now);
			pe_to_start_now = NULL;
		}
	}


	if (pe_to_start_last)
		start_copy(pe_to_start_last);

	return r;
}
