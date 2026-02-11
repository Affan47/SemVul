f2fs_update_nat_root(void)
{
	struct f2fs_nat_block *nat_blk = NULL;
	u_int64_t blk_size_bytes, nat_seg_blk_offset = 0;

	nat_blk = calloc(F2FS_BLKSIZE, 1);
	if(nat_blk == NULL) {
		MSG(1, "\tError: Calloc Failed for nat_blk!!!\n");
		return -1;
	}


	nat_blk->entries[le32_to_cpu(super_block.root_ino)].block_addr = cpu_to_le32(
		le32_to_cpu(super_block.main_blkaddr) +
		config.cur_seg[CURSEG_HOT_NODE] * config.blks_per_seg);
	nat_blk->entries[le32_to_cpu(super_block.root_ino)].ino = super_block.root_ino;


	nat_blk->entries[le32_to_cpu(super_block.node_ino)].block_addr = cpu_to_le32(1);
	nat_blk->entries[le32_to_cpu(super_block.node_ino)].ino = super_block.node_ino;


	nat_blk->entries[le32_to_cpu(super_block.meta_ino)].block_addr = cpu_to_le32(1);
	nat_blk->entries[le32_to_cpu(super_block.meta_ino)].ino = super_block.meta_ino;

	blk_size_bytes = 1 << le32_to_cpu(super_block.log_blocksize);
	nat_seg_blk_offset = le32_to_cpu(super_block.nat_blkaddr);
	nat_seg_blk_offset *= blk_size_bytes;

	if (dev_write(nat_blk, nat_seg_blk_offset, F2FS_BLKSIZE)) {
		MSG(1, "\tError: While writing the nat_blk set0 to disk!\n");
		return -1;
	}

	free(nat_blk);
	return 0;
}
