wb_congested_get_create(struct backing_dev_info *bdi, int blkcg_id, gfp_t gfp)
{
	struct bdi_writeback_congested *new_congested = NULL, *congested;
	struct rb_node **node, *parent;
	unsigned long flags;
retry:
	spin_lock_irqsave(&cgwb_lock, flags);

	node = &bdi->cgwb_congested_tree.rb_node;
	parent = NULL;

	while (*node != NULL) {
		parent = *node;
		congested = container_of(parent, struct bdi_writeback_congested,
					 rb_node);
		if (congested->blkcg_id < blkcg_id)
			node = &parent->rb_left;
		else if (congested->blkcg_id > blkcg_id)
			node = &parent->rb_right;
		else
			goto found;
	}

	if (new_congested) {

		congested = new_congested;
		new_congested = NULL;
		rb_link_node(&congested->rb_node, parent, node);
		rb_insert_color(&congested->rb_node, &bdi->cgwb_congested_tree);
		goto found;
	}

	spin_unlock_irqrestore(&cgwb_lock, flags);


	new_congested = kzalloc(sizeof(*new_congested), gfp);
	if (!new_congested)
		return NULL;

	atomic_set(&new_congested->refcnt, 0);
	new_congested->__bdi = bdi;
	new_congested->blkcg_id = blkcg_id;
	goto retry;

found:
	atomic_inc(&congested->refcnt);
	spin_unlock_irqrestore(&cgwb_lock, flags);
	kfree(new_congested);
	return congested;
}
