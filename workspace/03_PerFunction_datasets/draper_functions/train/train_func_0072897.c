migration_success_post_commit(struct dm_cache_migration *mg)
{
	unsigned long flags;
	struct cache *cache = mg->cache;

	if (mg->writeback) {
		DMWARN_LIMIT("%s: writeback unexpectedly triggered commit",
			     cache_device_name(cache));
		return;

	} else if (mg->demote) {
		cell_defer(cache, mg->old_ocell, mg->promote ? false : true);

		if (mg->promote) {
			mg->demote = false;

			spin_lock_irqsave(&cache->lock, flags);
			list_add_tail(&mg->list, &cache->quiesced_migrations);
			spin_unlock_irqrestore(&cache->lock, flags);

		} else {
			if (mg->invalidate)
				policy_remove_mapping(cache->policy, mg->old_oblock);
			free_io_migration(mg);
		}

	} else {
		if (mg->requeue_holder) {
			clear_dirty(cache, mg->new_oblock, mg->cblock);
			cell_defer(cache, mg->new_ocell, true);
		} else {


			set_dirty(cache, mg->new_oblock, mg->cblock);
			bio_endio(mg->new_ocell->holder);
			cell_defer(cache, mg->new_ocell, false);
		}
		free_io_migration(mg);
	}
}
