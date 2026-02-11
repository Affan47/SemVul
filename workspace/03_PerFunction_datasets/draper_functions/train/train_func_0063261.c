befs_load_sb(struct super_block *sb, befs_super_block * disk_sb)
{
	struct befs_sb_info *befs_sb = BEFS_SB(sb);


	if (disk_sb->fs_byte_order == BEFS_BYTEORDER_NATIVE_LE)
	    befs_sb->byte_order = BEFS_BYTESEX_LE;
	else if (disk_sb->fs_byte_order == BEFS_BYTEORDER_NATIVE_BE)
	    befs_sb->byte_order = BEFS_BYTESEX_BE;

	befs_sb->magic1 = fs32_to_cpu(sb, disk_sb->magic1);
	befs_sb->magic2 = fs32_to_cpu(sb, disk_sb->magic2);
	befs_sb->magic3 = fs32_to_cpu(sb, disk_sb->magic3);
	befs_sb->block_size = fs32_to_cpu(sb, disk_sb->block_size);
	befs_sb->block_shift = fs32_to_cpu(sb, disk_sb->block_shift);
	befs_sb->num_blocks = fs64_to_cpu(sb, disk_sb->num_blocks);
	befs_sb->used_blocks = fs64_to_cpu(sb, disk_sb->used_blocks);
	befs_sb->inode_size = fs32_to_cpu(sb, disk_sb->inode_size);

	befs_sb->blocks_per_ag = fs32_to_cpu(sb, disk_sb->blocks_per_ag);
	befs_sb->ag_shift = fs32_to_cpu(sb, disk_sb->ag_shift);
	befs_sb->num_ags = fs32_to_cpu(sb, disk_sb->num_ags);

	befs_sb->log_blocks = fsrun_to_cpu(sb, disk_sb->log_blocks);
	befs_sb->log_start = fs64_to_cpu(sb, disk_sb->log_start);
	befs_sb->log_end = fs64_to_cpu(sb, disk_sb->log_end);

	befs_sb->root_dir = fsrun_to_cpu(sb, disk_sb->root_dir);
	befs_sb->indices = fsrun_to_cpu(sb, disk_sb->indices);
	befs_sb->nls = NULL;

	return BEFS_OK;
}
