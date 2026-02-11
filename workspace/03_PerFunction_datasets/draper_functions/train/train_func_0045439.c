rsxx_blkdev_ioctl(struct block_device *bdev,
				 fmode_t mode,
				 unsigned int cmd,
				 unsigned long arg)
{
	struct rsxx_cardinfo *card = bdev->bd_disk->private_data;

	switch (cmd) {
	case RSXX_GETREG:
		return rsxx_reg_access(card, (void __user *)arg, 1);
	case RSXX_SETREG:
		return rsxx_reg_access(card, (void __user *)arg, 0);
	}

	return -ENOTTY;
}
