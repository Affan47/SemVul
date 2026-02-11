__list_lru_walk_one(struct list_lru *lru, int nid, int memcg_idx,
		    list_lru_walk_cb isolate, void *cb_arg,
		    unsigned long *nr_to_walk)
{

	struct list_lru_node *nlru = &lru->node[nid];
	struct list_lru_one *l;
	struct list_head *item, *n;
	unsigned long isolated = 0;

	spin_lock(&nlru->lock);
	l = list_lru_from_memcg_idx(nlru, memcg_idx);
restart:
	list_for_each_safe(item, n, &l->list) {
		enum lru_status ret;


		if (!*nr_to_walk)
			break;
		--*nr_to_walk;

		ret = isolate(item, l, &nlru->lock, cb_arg);
		switch (ret) {
		case LRU_REMOVED_RETRY:
			assert_spin_locked(&nlru->lock);
		case LRU_REMOVED:
			isolated++;
			nlru->nr_items--;


			if (ret == LRU_REMOVED_RETRY)
				goto restart;
			break;
		case LRU_ROTATE:
			list_move_tail(item, &l->list);
			break;
		case LRU_SKIP:
			break;
		case LRU_RETRY:


			assert_spin_locked(&nlru->lock);
			goto restart;
		default:
			BUG();
		}
	}

	spin_unlock(&nlru->lock);
	return isolated;
}
