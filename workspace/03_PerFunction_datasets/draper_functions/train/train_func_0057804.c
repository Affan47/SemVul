process_slot(struct cache_slot *slot)
{
	int err;

	err = open_slot(slot);
	if (!err && slot->match) {
		if (is_expired(slot)) {
			if (!lock_slot(slot)) {


				if (is_modified(slot) || fill_slot(slot)) {
					unlock_slot(slot, 0);
					close_lock(slot);
				} else {
					close_slot(slot);
					unlock_slot(slot, 1);
					slot->cache_fd = slot->lock_fd;
				}
			}
		}
		if ((err = print_slot(slot)) != 0) {
			cache_log("[cgit] error printing cache %s: %s (%d)\n",
				  slot->cache_name,
				  strerror(err),
				  err);
		}
		close_slot(slot);
		return err;
	}


	close_slot(slot);
	if ((err = lock_slot(slot)) != 0) {
		cache_log("[cgit] Unable to lock slot %s: %s (%d)\n",
			  slot->lock_name, strerror(err), err);
		slot->fn(slot->cbdata);
		return 0;
	}

	if ((err = fill_slot(slot)) != 0) {
		cache_log("[cgit] Unable to fill slot %s: %s (%d)\n",
			  slot->lock_name, strerror(err), err);
		unlock_slot(slot, 0);
		close_lock(slot);
		slot->fn(slot->cbdata);
		return 0;
	}


	slot->cache_fd = slot->lock_fd;
	unlock_slot(slot, 1);
	if ((err = print_slot(slot)) != 0) {
		cache_log("[cgit] error printing cache %s: %s (%d)\n",
			  slot->cache_name,
			  strerror(err),
			  err);
	}
	close_slot(slot);
	return err;
}
