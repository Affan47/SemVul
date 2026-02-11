smiapp_sysfs_nvm_read(struct device *dev, struct device_attribute *attr,
		      char *buf)
{
	struct v4l2_subdev *subdev = i2c_get_clientdata(to_i2c_client(dev));
	struct i2c_client *client = v4l2_get_subdevdata(subdev);
	struct smiapp_sensor *sensor = to_smiapp_sensor(subdev);
	unsigned int nbytes;

	if (!sensor->dev_init_done)
		return -EBUSY;

	if (!sensor->nvm_size) {

		sensor->nvm_size = sensor->platform_data->nvm_size;
		if (smiapp_set_power(subdev, 1) < 0)
			return -ENODEV;
		if (smiapp_read_nvm(sensor, sensor->nvm)) {
			dev_err(&client->dev, "nvm read failed\n");
			return -ENODEV;
		}
		smiapp_set_power(subdev, 0);
	}


	nbytes = min_t(unsigned int, sensor->nvm_size, PAGE_SIZE);
	memcpy(buf, sensor->nvm, nbytes);

	return nbytes;
}
