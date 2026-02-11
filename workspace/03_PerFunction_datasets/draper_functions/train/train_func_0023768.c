hdhomerun_channel_list_build_insert(struct hdhomerun_channel_list_t *channel_list, struct hdhomerun_channel_entry_t *entry)
{
	struct hdhomerun_channel_entry_t *prev = NULL;
	struct hdhomerun_channel_entry_t *next = channel_list->head;

	while (next) {
		if (next->frequency > entry->frequency) {
			break;
		}

		prev = next;
		next = next->next;
	}

	entry->prev = prev;
	entry->next = next;

	if (prev) {
		prev->next = entry;
	} else {
		channel_list->head = entry;
	}

	if (next) {
		next->prev = entry;
	} else {
		channel_list->tail = entry;
	}
}
