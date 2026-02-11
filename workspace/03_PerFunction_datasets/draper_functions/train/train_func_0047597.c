memcg_init_list_lru(struct list_lru *lru, bool memcg_aware)
{
	int i;

	if (!memcg_aware)
		return 0;

	for_each_node(i) {
		if (memcg_init_list_lru_node(&lru->node[i]))
			goto fail;
	}
	return 0;
fail:
	for (i = i - 1; i >= 0; i--) {
		if (!lru->node[i].memcg_lrus)
			continue;
		memcg_destroy_list_lru_node(&lru->node[i]);
	}
	return -ENOMEM;
}
