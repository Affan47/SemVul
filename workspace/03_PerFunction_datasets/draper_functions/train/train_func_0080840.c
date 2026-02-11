sr_probe(struct device *dev)
{
	struct scsi_device *sdev = to_scsi_device(dev);
	struct gendisk *disk;
	struct scsi_cd *cd;
	int minor, error;

	scsi_autopm_get_device(sdev);
	error = -ENODEV;
	if (sdev->type != TYPE_ROM && sdev->type != TYPE_WORM)
		goto fail;

	error = -ENOMEM;
	cd = kzalloc(sizeof(*cd), GFP_KERNEL);
	if (!cd)
		goto fail;

	kref_init(&cd->kref);

	disk = alloc_disk(1);
	if (!disk)
		goto fail_free;

	spin_lock(&sr_index_lock);
	minor = find_first_zero_bit(sr_index_bits, SR_DISKS);
	if (minor == SR_DISKS) {
		spin_unlock(&sr_index_lock);
		error = -EBUSY;
		goto fail_put;
	}
	__set_bit(minor, sr_index_bits);
	spin_unlock(&sr_index_lock);

	disk->major = SCSI_CDROM_MAJOR;
	disk->first_minor = minor;
	sprintf(disk->disk_name, "sr%d", minor);
	disk->fops = &sr_bdops;
	disk->flags = GENHD_FL_CD | GENHD_FL_BLOCK_EVENTS_ON_EXCL_WRITE;
	disk->events = DISK_EVENT_MEDIA_CHANGE | DISK_EVENT_EJECT_REQUEST;

	blk_queue_rq_timeout(sdev->request_queue, SR_TIMEOUT);

	cd->device = sdev;
	cd->disk = disk;
	cd->driver = &sr_template;
	cd->disk = disk;
	cd->capacity = 0x1fffff;
	cd->device->changed = 1;
	cd->media_present = 1;
	cd->use = 1;
	cd->readcd_known = 0;
	cd->readcd_cdda = 0;

	cd->cdi.ops = &sr_dops;
	cd->cdi.handle = cd;
	cd->cdi.mask = 0;
	cd->cdi.capacity = 1;
	sprintf(cd->cdi.name, "sr%d", minor);

	sdev->sector_size = 2048;


	get_capabilities(cd);
	sr_vendor_init(cd);

	disk->driverfs_dev = &sdev->sdev_gendev;
	set_capacity(disk, cd->capacity);
	disk->private_data = &cd->driver;
	disk->queue = sdev->request_queue;
	cd->cdi.disk = disk;

	if (register_cdrom(&cd->cdi))
		goto fail_put;


	blk_pm_runtime_init(sdev->request_queue, dev);

	dev_set_drvdata(dev, cd);
	disk->flags |= GENHD_FL_REMOVABLE;
	add_disk(disk);

	sdev_printk(KERN_DEBUG, sdev,
		    "Attached scsi CD-ROM %s\n", cd->cdi.name);
	scsi_autopm_put_device(cd->device);

	return 0;

fail_put:
	put_disk(disk);
fail_free:
	kfree(cd);
fail:
	scsi_autopm_put_device(sdev);
	return error;
}
