memcg_init_list_lru_node(struct list_lru_node *nlru)
{
	int size = memcg_nr_cache_ids;

	nlru->memcg_lrus = kmalloc(size * sizeof(void *), GFP_KERNEL);
	if (!nlru->memcg_lrus)
		return -ENOMEM;

	if (__memcg_init_list_lru_node(nlru->memcg_lrus, 0, size)) {
		kfree(nlru->memcg_lrus);
		return -ENOMEM;
	}

	return 0;
}
