firmware_map_find_entry_in_list(u64 start, u64 end, const char *type,
				struct list_head *list)
{
	struct firmware_map_entry *entry;

	list_for_each_entry(entry, list, list)
		if ((entry->start == start) && (entry->end == end) &&
		    (!strcmp(entry->type, type))) {
			return entry;
		}

	return NULL;
}
