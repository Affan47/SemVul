count_inode_extrefs(struct btrfs_root *root,
			       struct inode *inode, struct btrfs_path *path)
{
	int ret = 0;
	int name_len;
	unsigned int nlink = 0;
	u32 item_size;
	u32 cur_offset = 0;
	u64 inode_objectid = btrfs_ino(inode);
	u64 offset = 0;
	unsigned long ptr;
	struct btrfs_inode_extref *extref;
	struct extent_buffer *leaf;

	while (1) {
		ret = btrfs_find_one_extref(root, inode_objectid, offset, path,
					    &extref, &offset);
		if (ret)
			break;

		leaf = path->nodes[0];
		item_size = btrfs_item_size_nr(leaf, path->slots[0]);
		ptr = btrfs_item_ptr_offset(leaf, path->slots[0]);
		cur_offset = 0;

		while (cur_offset < item_size) {
			extref = (struct btrfs_inode_extref *) (ptr + cur_offset);
			name_len = btrfs_inode_extref_name_len(leaf, extref);

			nlink++;

			cur_offset += name_len + sizeof(*extref);
		}

		offset++;
		btrfs_release_path(path);
	}
	btrfs_release_path(path);

	if (ret < 0 && ret != -ENOENT)
		return ret;
	return nlink;
}
