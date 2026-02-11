hash_table_apply(hash_table_t * h, void (* function)(item_t * item)) {
	item_t * cur;
	unsigned int i;

	assert(h);

	for (i = 0; i < h->entries; i++) {
		cur = h->entry[i].head;
		while ( cur != NULL ) {
			function(cur);
			cur = cur->next;
		}
	}
}
