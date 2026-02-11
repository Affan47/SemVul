init_dvbdev(void)
{
	int retval;
	dev_t dev = MKDEV(DVB_MAJOR, 0);

	if ((retval = register_chrdev_region(dev, MAX_DVB_MINORS, "DVB")) != 0) {
		printk(KERN_ERR "dvb-core: unable to get major %d\n", DVB_MAJOR);
		return retval;
	}

	cdev_init(&dvb_device_cdev, &dvb_device_fops);
	if ((retval = cdev_add(&dvb_device_cdev, dev, MAX_DVB_MINORS)) != 0) {
		printk(KERN_ERR "dvb-core: unable register character device\n");
		goto error;
	}

	dvb_class = class_create(THIS_MODULE, "dvb");
	if (IS_ERR(dvb_class)) {
		retval = PTR_ERR(dvb_class);
		goto error;
	}
	dvb_class->dev_uevent = dvb_uevent;
	dvb_class->devnode = dvb_devnode;
	return 0;

error:
	cdev_del(&dvb_device_cdev);
	unregister_chrdev_region(dev, MAX_DVB_MINORS);
	return retval;
}
