add_system_zone(struct ext4_sb_info *sbi,
			   ext4_fsblk_t start_blk,
			   unsigned int count)
{
	struct ext4_system_zone *new_entry = NULL, *entry;
	struct rb_node **n = &sbi->system_blks.rb_node, *node;
	struct rb_node *parent = NULL, *new_node = NULL;

	while (*n) {
		parent = *n;
		entry = rb_entry(parent, struct ext4_system_zone, node);
		if (start_blk < entry->start_blk)
			n = &(*n)->rb_left;
		else if (start_blk >= (entry->start_blk + entry->count))
			n = &(*n)->rb_right;
		else {
			if (start_blk + count > (entry->start_blk +
						 entry->count))
				entry->count = (start_blk + count -
						entry->start_blk);
			new_node = *n;
			new_entry = rb_entry(new_node, struct ext4_system_zone,
					     node);
			break;
		}
	}

	if (!new_entry) {
		new_entry = kmem_cache_alloc(ext4_system_zone_cachep,
					     GFP_KERNEL);
		if (!new_entry)
			return -ENOMEM;
		new_entry->start_blk = start_blk;
		new_entry->count = count;
		new_node = &new_entry->node;

		rb_link_node(new_node, parent, n);
		rb_insert_color(new_node, &sbi->system_blks);
	}


	node = rb_prev(new_node);
	if (node) {
		entry = rb_entry(node, struct ext4_system_zone, node);
		if (can_merge(entry, new_entry)) {
			new_entry->start_blk = entry->start_blk;
			new_entry->count += entry->count;
			rb_erase(node, &sbi->system_blks);
			kmem_cache_free(ext4_system_zone_cachep, entry);
		}
	}


	node = rb_next(new_node);
	if (node) {
		entry = rb_entry(node, struct ext4_system_zone, node);
		if (can_merge(new_entry, entry)) {
			new_entry->count += entry->count;
			rb_erase(node, &sbi->system_blks);
			kmem_cache_free(ext4_system_zone_cachep, entry);
		}
	}
	return 0;
}
