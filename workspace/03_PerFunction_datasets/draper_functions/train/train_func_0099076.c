hq_entry_exists(ulong value)
{
	struct hash_table *ht;
	struct hq_entry *list_entry;
	long hqi;

	if (!(pc->flags & HASH))
		return FALSE;

	ht = &hash_table;

	if (ht->flags & (HASH_QUEUE_NONE))
		return FALSE;

	if (!(ht->flags & HASH_QUEUE_OPEN))
		return FALSE;

	hqi = HQ_INDEX(value);
	list_entry = ht->memptr + ht->queue_heads[hqi].next;

	while (TRUE) {
		if (list_entry->value == value)
			return TRUE;

		if (list_entry->next >= ht->count) {
			error(INFO, corrupt_hq,
				list_entry->value,
				list_entry->next,
 				list_entry->order);
			ht->flags |= HASH_QUEUE_NONE;
			return FALSE;
		}

		if (list_entry->next == 0)
			break;

		list_entry = ht->memptr + list_entry->next;
	}

	return FALSE;
}
