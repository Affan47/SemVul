nvme_compat_ioctl(struct block_device *bdev, fmode_t mode,
			unsigned int cmd, unsigned long arg)
{
	switch (cmd) {
	case SG_IO:
		return -ENOIOCTLCMD;
	}
	return nvme_ioctl(bdev, mode, cmd, arg);
}
