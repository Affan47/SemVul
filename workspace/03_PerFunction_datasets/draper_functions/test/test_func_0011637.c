store_ideapad_fan(struct device *dev,
				 struct device_attribute *attr,
				 const char *buf, size_t count)
{
	int ret, state;
	struct ideapad_private *priv = dev_get_drvdata(dev);

	if (!count)
		return 0;
	if (sscanf(buf, "%i", &state) != 1)
		return -EINVAL;
	if (state < 0 || state > 4 || state == 3)
		return -EINVAL;
	ret = write_ec_cmd(priv->adev->handle, VPCCMD_W_FAN, state);
	if (ret < 0)
		return -EIO;
	return count;
}
