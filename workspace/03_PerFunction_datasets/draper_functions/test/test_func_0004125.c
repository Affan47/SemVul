ast_hashtab_get_stats(struct ast_hashtab *tab, int *biggest_bucket_size, int *resize_count, int *num_objects, int *num_buckets)
{

	if (tab->do_locking)
		ast_rwlock_rdlock(&tab->lock);
	*biggest_bucket_size = tab->largest_bucket_size;
	*resize_count = tab->resize_count;
	*num_objects = tab->hash_tab_elements;
	*num_buckets = tab->hash_tab_size;
	if (tab->do_locking)
		ast_rwlock_unlock(&tab->lock);
}
