fd_execute_unmap(struct se_cmd *cmd, sector_t lba, sector_t nolb)
{
	struct file *file = FD_DEV(cmd->se_dev)->fd_file;
	struct inode *inode = file->f_mapping->host;
	int ret;

	if (!nolb) {
		return 0;
	}

	if (cmd->se_dev->dev_attrib.pi_prot_type) {
		ret = fd_do_prot_unmap(cmd, lba, nolb);
		if (ret)
			return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	}

	if (S_ISBLK(inode->i_mode)) {

		struct block_device *bdev = inode->i_bdev;
		struct se_device *dev = cmd->se_dev;

		ret = blkdev_issue_discard(bdev,
					   target_to_linux_sector(dev, lba),
					   target_to_linux_sector(dev,  nolb),
					   GFP_KERNEL, 0);
		if (ret < 0) {
			pr_warn("FILEIO: blkdev_issue_discard() failed: %d\n",
				ret);
			return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
		}
	} else {

		struct se_device *se_dev = cmd->se_dev;
		loff_t pos = lba * se_dev->dev_attrib.block_size;
		unsigned int len = nolb * se_dev->dev_attrib.block_size;
		int mode = FALLOC_FL_PUNCH_HOLE | FALLOC_FL_KEEP_SIZE;

		if (!file->f_op->fallocate)
			return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

		ret = file->f_op->fallocate(file, mode, pos, len);
		if (ret < 0) {
			pr_warn("FILEIO: fallocate() failed: %d\n", ret);
			return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
		}
	}

	return 0;
}
