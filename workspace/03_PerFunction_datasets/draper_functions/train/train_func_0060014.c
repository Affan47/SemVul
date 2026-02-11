hash_list_head(const hash_list_t *hl)
{
	struct hash_list_item *item;

	hash_list_check(hl);

	item = elist_head(&hl->list);
	return NULL == item ? NULL : deconstify_pointer(item->key);
}
