iblock_execute_unmap(struct se_cmd *cmd, sector_t lba, sector_t nolb)
{
	struct block_device *bdev = IBLOCK_DEV(cmd->se_dev)->ibd_bd;
	struct se_device *dev = cmd->se_dev;
	int ret;

	ret = blkdev_issue_discard(bdev,
				   target_to_linux_sector(dev, lba),
				   target_to_linux_sector(dev,  nolb),
				   GFP_KERNEL, 0);
	if (ret < 0) {
		pr_err("blkdev_issue_discard() failed: %d\n", ret);
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	}

	return 0;
}
