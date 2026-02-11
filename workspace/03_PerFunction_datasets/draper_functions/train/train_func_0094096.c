sysfs_set_reg(struct device *dev,
			     struct device_attribute *attr,
			     const char *buf, size_t count, u32 reg)
{
	struct dpot_data *data = dev_get_drvdata(dev);
	unsigned long value;
	int err;

	if (reg & DPOT_ADDR_OTP_EN) {
		if (!strncmp(buf, "enabled", sizeof("enabled")))
			set_bit(DPOT_RDAC_MASK & reg, data->otp_en_mask);
		else
			clear_bit(DPOT_RDAC_MASK & reg, data->otp_en_mask);

		return count;
	}

	if ((reg & DPOT_ADDR_OTP) &&
		!test_bit(DPOT_RDAC_MASK & reg, data->otp_en_mask))
		return -EPERM;

	err = kstrtoul(buf, 10, &value);
	if (err)
		return err;

	if (value > data->rdac_mask)
		value = data->rdac_mask;

	mutex_lock(&data->update_lock);
	dpot_write(data, reg, value);
	if (reg & DPOT_ADDR_EEPROM)
		msleep(26);
	else if (reg & DPOT_ADDR_OTP)
		msleep(400);
	mutex_unlock(&data->update_lock);

	return count;
}
