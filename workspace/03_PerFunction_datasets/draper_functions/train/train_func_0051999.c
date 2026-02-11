device_not_write_same_capable(struct dm_target *ti, struct dm_dev *dev,
					 sector_t start, sector_t len, void *data)
{
	struct request_queue *q = bdev_get_queue(dev->bdev);

	return q && !q->limits.max_write_same_sectors;
}
