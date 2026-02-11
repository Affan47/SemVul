destroy_addr_hash_val(gpointer value)
{
	GSList *list = (GSList*) value;
	GSList *walk;

	for(walk = list; walk; walk = walk->next) {
		AddrDupListEntry *entry = (AddrDupListEntry*) walk->data;
		if(entry && entry->book_path)
			g_free(entry->book_path);
		if(entry)
			g_free(entry);
	}
	if(list)
		g_slist_free(list);
}
