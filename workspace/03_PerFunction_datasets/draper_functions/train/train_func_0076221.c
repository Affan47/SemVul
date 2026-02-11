delete_process_ht(hash_table_t * fd_mappings, int32_t pid) {
	item_t * process_ht_item;

	if ( (process_ht_item = hash_table_find(fd_mappings, &pid)) != NULL ) {
		hash_table_remove(fd_mappings, &pid);
	} else {
		ERRORPRINTF("Can not find pid %"PRIi32" when removing delete_process_ht\n", pid);
	}
}
