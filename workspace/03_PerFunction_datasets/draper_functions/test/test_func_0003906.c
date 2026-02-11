rv8803_nvram_write(struct file *filp, struct kobject *kobj,
				  struct bin_attribute *attr,
				  char *buf, loff_t off, size_t count)
{
	struct device *dev = kobj_to_dev(kobj);
	struct i2c_client *client = to_i2c_client(dev);
	int ret;

	ret = i2c_smbus_write_byte_data(client, RV8803_RAM, buf[0]);
	if (ret < 0)
		return ret;

	return 1;
}
