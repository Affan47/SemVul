ipath_expose_reset(struct device *dev)
{
	static int exposed;
	int ret;

	if (!exposed) {
		ret = device_create_file(dev, &dev_attr_reset);
		exposed = 1;
	} else {
		ret = 0;
	}

	return ret;
}
