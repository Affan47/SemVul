xhash_free(xhash_t* table)
{
	xhash_item_t* current_item = NULL;
	xhash_item_t* tmp = NULL;

	if (!table)
		return;
	HASH_ITER(hh, table->ht, current_item, tmp) {
		  HASH_DEL(table->ht, current_item);
		  xfree(current_item);
	}
	xfree(table);
}
