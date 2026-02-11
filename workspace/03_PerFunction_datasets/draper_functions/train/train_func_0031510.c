isl1208_sysfs_store_usr(struct device *dev,
			struct device_attribute *attr,
			const char *buf, size_t count)
{
	int usr = -1;

	if (buf[0] == '0' && (buf[1] == 'x' || buf[1] == 'X')) {
		if (sscanf(buf, "%x", &usr) != 1)
			return -EINVAL;
	} else {
		if (sscanf(buf, "%d", &usr) != 1)
			return -EINVAL;
	}

	if (usr < 0 || usr > 0xffff)
		return -EINVAL;

	return isl1208_i2c_set_usr(to_i2c_client(dev), usr) ? -EIO : count;
}
