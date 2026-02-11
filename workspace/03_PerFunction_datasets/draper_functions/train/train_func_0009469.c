free_debug_processing(
	struct kmem_cache *s, struct page *page,
	void *head, void *tail, int bulk_cnt,
	unsigned long addr, unsigned long *flags)
{
	struct kmem_cache_node *n = get_node(s, page_to_nid(page));
	void *object = head;
	int cnt = 0;

	spin_lock_irqsave(&n->list_lock, *flags);
	slab_lock(page);

	if (!check_slab(s, page))
		goto fail;

next_object:
	cnt++;

	if (!check_valid_pointer(s, page, object)) {
		slab_err(s, page, "Invalid object pointer 0x%p", object);
		goto fail;
	}

	if (on_freelist(s, page, object)) {
		object_err(s, page, object, "Object already free");
		goto fail;
	}

	if (!check_object(s, page, object, SLUB_RED_ACTIVE))
		goto out;

	if (unlikely(s != page->slab_cache)) {
		if (!PageSlab(page)) {
			slab_err(s, page, "Attempt to free object(0x%p) "
				"outside of slab", object);
		} else if (!page->slab_cache) {
			pr_err("SLUB <none>: no slab for object 0x%p.\n",
			       object);
			dump_stack();
		} else
			object_err(s, page, object,
					"page slab pointer corrupt.");
		goto fail;
	}

	if (s->flags & SLAB_STORE_USER)
		set_track(s, object, TRACK_FREE, addr);
	trace(s, page, object, 0);

	init_object(s, object, SLUB_RED_INACTIVE);


	if (object != tail) {
		object = get_freepointer(s, object);
		goto next_object;
	}
out:
	if (cnt != bulk_cnt)
		slab_err(s, page, "Bulk freelist count(%d) invalid(%d)\n",
			 bulk_cnt, cnt);

	slab_unlock(page);


	return n;

fail:
	slab_unlock(page);
	spin_unlock_irqrestore(&n->list_lock, *flags);
	slab_fix(s, "Object at 0x%p not freed", object);
	return NULL;
}
