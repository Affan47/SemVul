__write_initial_superblock(struct dm_pool_metadata *pmd)
{
	int r;
	struct dm_block *sblock;
	struct thin_disk_superblock *disk_super;
	sector_t bdev_size = i_size_read(pmd->bdev->bd_inode) >> SECTOR_SHIFT;

	if (bdev_size > THIN_METADATA_MAX_SECTORS)
		bdev_size = THIN_METADATA_MAX_SECTORS;

	r = dm_sm_commit(pmd->data_sm);
	if (r < 0)
		return r;

	r = dm_tm_pre_commit(pmd->tm);
	if (r < 0)
		return r;

	r = save_sm_roots(pmd);
	if (r < 0)
		return r;

	r = superblock_lock_zero(pmd, &sblock);
	if (r)
		return r;

	disk_super = dm_block_data(sblock);
	disk_super->flags = 0;
	memset(disk_super->uuid, 0, sizeof(disk_super->uuid));
	disk_super->magic = cpu_to_le64(THIN_SUPERBLOCK_MAGIC);
	disk_super->version = cpu_to_le32(THIN_VERSION);
	disk_super->time = 0;
	disk_super->trans_id = 0;
	disk_super->held_root = 0;

	copy_sm_roots(pmd, disk_super);

	disk_super->data_mapping_root = cpu_to_le64(pmd->root);
	disk_super->device_details_root = cpu_to_le64(pmd->details_root);
	disk_super->metadata_block_size = cpu_to_le32(THIN_METADATA_BLOCK_SIZE);
	disk_super->metadata_nr_blocks = cpu_to_le64(bdev_size >> SECTOR_TO_BLOCK_SHIFT);
	disk_super->data_block_size = cpu_to_le32(pmd->data_block_size);

	return dm_tm_commit(pmd->tm, sblock);
}
