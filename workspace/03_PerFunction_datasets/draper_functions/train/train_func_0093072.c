bch_btree_gc_finish(struct cache_set *c)
{
	size_t available = 0;
	struct bucket *b;
	struct cache *ca;
	unsigned i;

	mutex_lock(&c->bucket_lock);

	set_gc_sectors(c);
	c->gc_mark_valid = 1;
	c->need_gc	= 0;

	for (i = 0; i < KEY_PTRS(&c->uuid_bucket); i++)
		SET_GC_MARK(PTR_BUCKET(c, &c->uuid_bucket, i),
			    GC_MARK_METADATA);


	rcu_read_lock();
	for (i = 0; i < c->nr_uuids; i++) {
		struct bcache_device *d = c->devices[i];
		struct cached_dev *dc;
		struct keybuf_key *w, *n;
		unsigned j;

		if (!d || UUID_FLASH_ONLY(&c->uuids[i]))
			continue;
		dc = container_of(d, struct cached_dev, disk);

		spin_lock(&dc->writeback_keys.lock);
		rbtree_postorder_for_each_entry_safe(w, n,
					&dc->writeback_keys.keys, node)
			for (j = 0; j < KEY_PTRS(&w->key); j++)
				SET_GC_MARK(PTR_BUCKET(c, &w->key, j),
					    GC_MARK_DIRTY);
		spin_unlock(&dc->writeback_keys.lock);
	}
	rcu_read_unlock();

	for_each_cache(ca, c, i) {
		uint64_t *i;

		ca->invalidate_needs_gc = 0;

		for (i = ca->sb.d; i < ca->sb.d + ca->sb.keys; i++)
			SET_GC_MARK(ca->buckets + *i, GC_MARK_METADATA);

		for (i = ca->prio_buckets;
		     i < ca->prio_buckets + prio_buckets(ca) * 2; i++)
			SET_GC_MARK(ca->buckets + *i, GC_MARK_METADATA);

		for_each_bucket(b, ca) {
			c->need_gc	= max(c->need_gc, bucket_gc_gen(b));

			if (atomic_read(&b->pin))
				continue;

			BUG_ON(!GC_MARK(b) && GC_SECTORS_USED(b));

			if (!GC_MARK(b) || GC_MARK(b) == GC_MARK_RECLAIMABLE)
				available++;
		}
	}

	mutex_unlock(&c->bucket_lock);
	return available;
}
