list_lru_add(struct list_lru *lru, struct list_head *item)
{
	int nid = page_to_nid(virt_to_page(item));
	struct list_lru_node *nlru = &lru->node[nid];
	struct list_lru_one *l;

	spin_lock(&nlru->lock);
	if (list_empty(item)) {
		l = list_lru_from_kmem(nlru, item);
		list_add_tail(item, &l->list);
		l->nr_items++;
		nlru->nr_items++;
		spin_unlock(&nlru->lock);
		return true;
	}
	spin_unlock(&nlru->lock);
	return false;
}
