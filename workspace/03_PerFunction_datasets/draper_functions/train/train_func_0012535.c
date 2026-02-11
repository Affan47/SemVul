activate_bit_delay(struct r5conf *conf,
	struct list_head *temp_inactive_list)
{

	struct list_head head;
	list_add(&head, &conf->bitmap_list);
	list_del_init(&conf->bitmap_list);
	while (!list_empty(&head)) {
		struct stripe_head *sh = list_entry(head.next, struct stripe_head, lru);
		int hash;
		list_del_init(&sh->lru);
		atomic_inc(&sh->count);
		hash = sh->hash_lock_index;
		__release_stripe(conf, sh, &temp_inactive_list[hash]);
	}
}
