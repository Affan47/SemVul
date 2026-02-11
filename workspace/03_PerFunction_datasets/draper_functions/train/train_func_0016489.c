squashfs_get_id(struct super_block *sb, unsigned int index,
					unsigned int *id)
{
	struct squashfs_sb_info *msblk = sb->s_fs_info;
	int block = SQUASHFS_ID_BLOCK(index);
	int offset = SQUASHFS_ID_BLOCK_OFFSET(index);
	u64 start_block = le64_to_cpu(msblk->id_table[block]);
	__le32 disk_id;
	int err;

	err = squashfs_read_metadata(sb, &disk_id, &start_block, &offset,
							sizeof(disk_id));
	if (err < 0)
		return err;

	*id = le32_to_cpu(disk_id);
	return 0;
}
