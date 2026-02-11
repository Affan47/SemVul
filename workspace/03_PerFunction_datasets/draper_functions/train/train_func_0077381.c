au0828_i2c_register(struct au0828_dev *dev)
{
	dprintk(1, "%s()\n", __func__);

	dev->i2c_adap = au0828_i2c_adap_template;
	dev->i2c_algo = au0828_i2c_algo_template;
	dev->i2c_client = au0828_i2c_client_template;

	dev->i2c_adap.dev.parent = &dev->usbdev->dev;

	strlcpy(dev->i2c_adap.name, KBUILD_MODNAME,
		sizeof(dev->i2c_adap.name));

	dev->i2c_adap.algo = &dev->i2c_algo;
	dev->i2c_adap.algo_data = dev;
#ifdef CONFIG_VIDEO_AU0828_V4L2
	i2c_set_adapdata(&dev->i2c_adap, &dev->v4l2_dev);
#else
	i2c_set_adapdata(&dev->i2c_adap, dev);
#endif
	i2c_add_adapter(&dev->i2c_adap);

	dev->i2c_client.adapter = &dev->i2c_adap;

	if (0 == dev->i2c_rc) {
		pr_info("i2c bus registered\n");
		if (i2c_scan)
			do_i2c_scan(KBUILD_MODNAME, &dev->i2c_client);
	} else
		pr_info("i2c bus register FAILED\n");

	return dev->i2c_rc;
}
