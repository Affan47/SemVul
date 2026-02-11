revitalize_entry(struct message *entry, bool force)
{
	struct message **relocated;
	struct message *prev;
	unsigned chunk_idx;


	if (!force && settings_is_leaf())
		return;


	relocated = get_next_slot(FALSE, &chunk_idx);


	if (chunk_idx == entry->chunk_idx)
		return;


	advance_slot();
	prev = *relocated;

	if (prev != NULL) {
		message_check(prev, chunk_idx);
		g_assert(prev->slot == relocated);
		clean_entry(prev);
		WFREE(prev);
		routing.count--;
		gnet_stats_dec_general(GNR_ROUTING_TABLE_COUNT);
	}


	*relocated = entry;
	*(entry->slot) = NULL;
	entry->slot = relocated;
	entry->chunk_idx = chunk_idx;

	message_check(entry, chunk_idx);
}
