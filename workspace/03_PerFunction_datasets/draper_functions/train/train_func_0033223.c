__add_prelim_ref(struct list_head *head, u64 root_id,
			    struct btrfs_key *key, int level,
			    u64 parent, u64 wanted_disk_byte, int count,
			    gfp_t gfp_mask)
{
	struct __prelim_ref *ref;

	if (root_id == BTRFS_DATA_RELOC_TREE_OBJECTID)
		return 0;

	ref = kmem_cache_alloc(btrfs_prelim_ref_cache, gfp_mask);
	if (!ref)
		return -ENOMEM;

	ref->root_id = root_id;
	if (key) {
		ref->key_for_search = *key;


		if (ref->key_for_search.type == BTRFS_EXTENT_DATA_KEY &&
		    ref->key_for_search.offset >= LLONG_MAX)
			ref->key_for_search.offset = 0;
	} else {
		memset(&ref->key_for_search, 0, sizeof(ref->key_for_search));
	}

	ref->inode_list = NULL;
	ref->level = level;
	ref->count = count;
	ref->parent = parent;
	ref->wanted_disk_byte = wanted_disk_byte;
	list_add_tail(&ref->list, head);

	return 0;
}
