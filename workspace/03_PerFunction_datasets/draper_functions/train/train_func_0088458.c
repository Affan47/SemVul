ssd_unregister_event_notifier(struct block_device *bdev)
{
	struct ssd_device *dev;

	if (!bdev || !(bdev->bd_disk)) {
		return -EINVAL;
	}

	dev = bdev->bd_disk->private_data;
	dev->event_call = NULL;

	return 0;
}
