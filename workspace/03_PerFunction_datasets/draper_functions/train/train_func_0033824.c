adf_cfg_dev_add(struct adf_accel_dev *accel_dev)
{
	struct adf_cfg_device_data *dev_cfg_data;

	dev_cfg_data = kzalloc(sizeof(*dev_cfg_data), GFP_KERNEL);
	if (!dev_cfg_data)
		return -ENOMEM;
	INIT_LIST_HEAD(&dev_cfg_data->sec_list);
	init_rwsem(&dev_cfg_data->lock);
	accel_dev->cfg = dev_cfg_data;


	dev_cfg_data->debug = debugfs_create_file("dev_cfg", S_IRUSR,
						  accel_dev->debugfs_dir,
						  dev_cfg_data,
						  &qat_dev_cfg_fops);
	if (!dev_cfg_data->debug) {
		dev_err(&GET_DEV(accel_dev),
			"Failed to create qat cfg debugfs entry.\n");
		kfree(dev_cfg_data);
		accel_dev->cfg = NULL;
		return -EFAULT;
	}
	return 0;
}
