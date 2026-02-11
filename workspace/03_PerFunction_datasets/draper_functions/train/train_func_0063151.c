hdaps_temp1_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	u8 uninitialized_var(temp);
	int ret;

	ret = hdaps_readb_one(HDAPS_PORT_TEMP1, &temp);
	if (ret)
		return ret;

	return sprintf(buf, "%u\n", temp);
}
