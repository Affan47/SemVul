dbell_index_table_add(struct dbell_entry *entry)
{
	u32 bucket;
	u32 new_notify_idx;

	vmci_resource_get(&entry->resource);

	spin_lock_bh(&vmci_doorbell_it.lock);


	if (max_notify_idx < PAGE_SIZE || notify_idx_count < PAGE_SIZE) {
		if (last_notify_idx_released < max_notify_idx &&
		    !dbell_index_table_find(last_notify_idx_released)) {
			new_notify_idx = last_notify_idx_released;
			last_notify_idx_released = PAGE_SIZE;
		} else {
			bool reused = false;
			new_notify_idx = last_notify_idx_reserved;
			if (notify_idx_count + 1 < max_notify_idx) {
				do {
					if (!dbell_index_table_find
					    (new_notify_idx)) {
						reused = true;
						break;
					}
					new_notify_idx = (new_notify_idx + 1) %
					    max_notify_idx;
				} while (new_notify_idx !=
					 last_notify_idx_released);
			}
			if (!reused) {
				new_notify_idx = max_notify_idx;
				max_notify_idx++;
			}
		}
	} else {
		new_notify_idx = (last_notify_idx_reserved + 1) % PAGE_SIZE;
	}

	last_notify_idx_reserved = new_notify_idx;
	notify_idx_count++;

	entry->idx = new_notify_idx;
	bucket = VMCI_DOORBELL_HASH(entry->idx);
	hlist_add_head(&entry->node, &vmci_doorbell_it.entries[bucket]);

	spin_unlock_bh(&vmci_doorbell_it.lock);
}
