btrfs_writeback_inodes_sb_nr(struct btrfs_root *root,
					 unsigned long nr_pages, int nr_items)
{
	struct super_block *sb = root->fs_info->sb;

	if (down_read_trylock(&sb->s_umount)) {
		writeback_inodes_sb_nr(sb, nr_pages, WB_REASON_FS_FREE_SPACE);
		up_read(&sb->s_umount);
	} else {


		btrfs_start_delalloc_roots(root->fs_info, 0, nr_items);
		if (!current->journal_info)
			btrfs_wait_ordered_roots(root->fs_info, nr_items);
	}
}
