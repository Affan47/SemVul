putall_functor(const void* item, void* data) {

	hashmap_item_t* hashmap_item = item;
	hashmap_t* dest = data;


	hashmap_item_t* cloned = malloc(sizeof(hashmap_item_t));
	cloned->key = hashmap_item->key;
	cloned->item = hashmap_item->item;
	cloned->owner = dest;

	hashmap_item_t* replaced = hashtable_add(dest->hashtable, cloned, NULL, NULL);
	if(replaced!=NULL) {
		free(replaced);
	}

	return 0;
}
