btrfs_find_name_in_ext_backref(struct btrfs_path *path, u64 ref_objectid,
				   const char *name, int name_len,
				   struct btrfs_inode_extref **extref_ret)
{
	struct extent_buffer *leaf;
	struct btrfs_inode_extref *extref;
	unsigned long ptr;
	unsigned long name_ptr;
	u32 item_size;
	u32 cur_offset = 0;
	int ref_name_len;

	leaf = path->nodes[0];
	item_size = btrfs_item_size_nr(leaf, path->slots[0]);
	ptr = btrfs_item_ptr_offset(leaf, path->slots[0]);


	while (cur_offset < item_size) {
		extref = (struct btrfs_inode_extref *) (ptr + cur_offset);
		name_ptr = (unsigned long)(&extref->name);
		ref_name_len = btrfs_inode_extref_name_len(leaf, extref);

		if (ref_name_len == name_len &&
		    btrfs_inode_extref_parent(leaf, extref) == ref_objectid &&
		    (memcmp_extent_buffer(leaf, name, name_ptr, name_len) == 0)) {
			if (extref_ret)
				*extref_ret = extref;
			return 1;
		}

		cur_offset += ref_name_len + sizeof(*extref);
	}
	return 0;
}
