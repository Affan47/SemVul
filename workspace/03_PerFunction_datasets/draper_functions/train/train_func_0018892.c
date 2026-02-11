btrfs_reloc_clone_csums(struct inode *inode, u64 file_pos, u64 len)
{
	struct btrfs_ordered_sum *sums;
	struct btrfs_ordered_extent *ordered;
	struct btrfs_root *root = BTRFS_I(inode)->root;
	int ret;
	u64 disk_bytenr;
	u64 new_bytenr;
	LIST_HEAD(list);

	ordered = btrfs_lookup_ordered_extent(inode, file_pos);
	BUG_ON(ordered->file_offset != file_pos || ordered->len != len);

	disk_bytenr = file_pos + BTRFS_I(inode)->index_cnt;
	ret = btrfs_lookup_csums_range(root->fs_info->csum_root, disk_bytenr,
				       disk_bytenr + len - 1, &list, 0);
	if (ret)
		goto out;

	while (!list_empty(&list)) {
		sums = list_entry(list.next, struct btrfs_ordered_sum, list);
		list_del_init(&sums->list);


		new_bytenr = ordered->start + (sums->bytenr - disk_bytenr);
		sums->bytenr = new_bytenr;

		btrfs_add_ordered_sum(inode, ordered, sums);
	}
out:
	btrfs_put_ordered_extent(ordered);
	return ret;
}
