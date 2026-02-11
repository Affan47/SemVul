rbd_dev_update_size(struct rbd_device *rbd_dev)
{
	sector_t size;
	bool removing;


	spin_lock_irq(&rbd_dev->lock);
	removing = test_bit(RBD_DEV_FLAG_REMOVING, &rbd_dev->flags);
	spin_unlock_irq(&rbd_dev->lock);


	if (!removing) {
		size = (sector_t)rbd_dev->mapping.size / SECTOR_SIZE;
		dout("setting size to %llu sectors", (unsigned long long)size);
		set_capacity(rbd_dev->disk, size);
		revalidate_disk(rbd_dev->disk);
	}
}
