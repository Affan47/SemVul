reada_add_block(struct reada_control *rc, u64 logical,
			   struct btrfs_key *top, int level, u64 generation)
{
	struct btrfs_root *root = rc->root;
	struct reada_extent *re;
	struct reada_extctl *rec;

	re = reada_find_extent(root, logical, top, level);
	if (!re)
		return -1;

	rec = kzalloc(sizeof(*rec), GFP_NOFS);
	if (!rec) {
		reada_extent_put(root->fs_info, re);
		return -ENOMEM;
	}

	rec->rc = rc;
	rec->generation = generation;
	atomic_inc(&rc->elems);

	spin_lock(&re->lock);
	list_add_tail(&rec->list, &re->extctl);
	spin_unlock(&re->lock);


	return 0;
}
