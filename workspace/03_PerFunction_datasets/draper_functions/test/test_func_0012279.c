ubi_add_volume(struct ubi_device *ubi, struct ubi_volume *vol)
{
	int err, vol_id = vol->vol_id;
	dev_t dev;

	dbg_gen("add volume %d", vol_id);


	cdev_init(&vol->cdev, &ubi_vol_cdev_operations);
	vol->cdev.owner = THIS_MODULE;
	dev = MKDEV(MAJOR(ubi->cdev.dev), vol->vol_id + 1);
	err = cdev_add(&vol->cdev, dev, 1);
	if (err) {
		ubi_err(ubi, "cannot add character device for volume %d, error %d",
			vol_id, err);
		return err;
	}

	vol->dev.release = vol_release;
	vol->dev.parent = &ubi->dev;
	vol->dev.devt = dev;
	vol->dev.class = &ubi_class;
	vol->dev.groups = volume_dev_groups;
	dev_set_name(&vol->dev, "%s_%d", ubi->ubi_name, vol->vol_id);
	err = device_register(&vol->dev);
	if (err)
		goto out_cdev;

	self_check_volumes(ubi);
	return err;

out_cdev:
	cdev_del(&vol->cdev);
	return err;
}
