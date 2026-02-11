btrfs_readdir(struct file *file, struct dirent *dirent)
{
	struct fs_info *fs = file->fs;
	struct inode *inode = file->inode;
	struct btrfs_disk_key search_key;
	struct btrfs_path path;
	struct btrfs_dir_item *dir_item;
	int ret;


	search_key.objectid = inode->ino;
	search_key.type = BTRFS_DIR_ITEM_KEY;
	search_key.offset = file->offset - 1;
	clear_path(&path);
	ret = search_tree(fs, fs_tree, &search_key, &path);

	if (ret) {
		if (btrfs_comp_keys_type(&search_key, &path.item.key))
			return -1;
	}

	dir_item = (struct btrfs_dir_item *)path.data;
	file->offset = path.item.key.offset;
	dirent->d_ino = dir_item->location.objectid;
	dirent->d_off = file->offset;
	dirent->d_reclen = offsetof(struct dirent, d_name)
		+ dir_item->name_len + 1;
	dirent->d_type = IFTODT(dir_item->type);
	memcpy(dirent->d_name, dir_item + 1, dir_item->name_len);
	dirent->d_name[dir_item->name_len] = '\0';

	return 0;
}
