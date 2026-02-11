cas_spare_recover(struct cas *cp, const gfp_t flags)
{
	struct list_head list, *elem, *tmp;
	int needed, i;


	INIT_LIST_HEAD(&list);
	spin_lock(&cp->rx_inuse_lock);
	list_splice_init(&cp->rx_inuse_list, &list);
	spin_unlock(&cp->rx_inuse_lock);

	list_for_each_safe(elem, tmp, &list) {
		cas_page_t *page = list_entry(elem, cas_page_t, list);


		if (page_count(page->buffer) > 1)
			continue;

		list_del(elem);
		spin_lock(&cp->rx_spare_lock);
		if (cp->rx_spares_needed > 0) {
			list_add(elem, &cp->rx_spare_list);
			cp->rx_spares_needed--;
			spin_unlock(&cp->rx_spare_lock);
		} else {
			spin_unlock(&cp->rx_spare_lock);
			cas_page_free(cp, page);
		}
	}


	if (!list_empty(&list)) {
		spin_lock(&cp->rx_inuse_lock);
		list_splice(&list, &cp->rx_inuse_list);
		spin_unlock(&cp->rx_inuse_lock);
	}

	spin_lock(&cp->rx_spare_lock);
	needed = cp->rx_spares_needed;
	spin_unlock(&cp->rx_spare_lock);
	if (!needed)
		return;


	INIT_LIST_HEAD(&list);
	i = 0;
	while (i < needed) {
		cas_page_t *spare = cas_page_alloc(cp, flags);
		if (!spare)
			break;
		list_add(&spare->list, &list);
		i++;
	}

	spin_lock(&cp->rx_spare_lock);
	list_splice(&list, &cp->rx_spare_list);
	cp->rx_spares_needed -= i;
	spin_unlock(&cp->rx_spare_lock);
}
