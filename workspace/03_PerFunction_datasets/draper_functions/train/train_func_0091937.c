memcg_update_list_lru_node(struct list_lru_node *nlru,
				      int old_size, int new_size)
{
	struct list_lru_memcg *old, *new;

	BUG_ON(old_size > new_size);

	old = nlru->memcg_lrus;
	new = kmalloc(new_size * sizeof(void *), GFP_KERNEL);
	if (!new)
		return -ENOMEM;

	if (__memcg_init_list_lru_node(new, old_size, new_size)) {
		kfree(new);
		return -ENOMEM;
	}

	memcpy(new, old, old_size * sizeof(void *));


	spin_lock_irq(&nlru->lock);
	nlru->memcg_lrus = new;
	spin_unlock_irq(&nlru->lock);

	kfree(old);
	return 0;
}
