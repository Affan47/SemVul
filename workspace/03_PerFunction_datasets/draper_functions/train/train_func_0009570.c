show_chip_temp(struct device *dev,
			      struct device_attribute *attr, char *buf)
{
	struct wm831x *wm831x = dev_get_drvdata(dev);
	int channel = to_sensor_dev_attr(attr)->index;
	int ret;

	ret = wm831x_auxadc_read(wm831x, channel);
	if (ret < 0)
		return ret;


	ret = 512180 - (ret * 1000);
	ret = DIV_ROUND_CLOSEST(ret * 10000, 10983);

	return sprintf(buf, "%d\n", ret);
}
