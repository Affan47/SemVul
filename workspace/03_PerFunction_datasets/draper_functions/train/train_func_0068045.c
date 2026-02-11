getEntry(const s8 *key)
{
	if (!key) return 0;

	OptionEntry *entry = mConfigEntrys;
	while (entry) {
		if (!strcmp(key, entry->key)) break;
		entry = entry->next;
	}

	return entry;
}
