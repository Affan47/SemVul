show_ltemp(struct device *dev,
			  struct device_attribute *devattr, char *buf)
{
	struct nct7904_data *data = dev_get_drvdata(dev);
	int ret;
	int temp;

	ret = nct7904_read_reg16(data, BANK_0, LTD_HV_REG);
	if (ret < 0)
		return ret;
	temp = ((ret & 0xff00) >> 5) | (ret & 0x7);
	temp = sign_extend32(temp, 10) * 125;

	return sprintf(buf, "%d\n", temp);
}
