pcf2123_show(struct device *dev, struct device_attribute *attr,
			    char *buffer)
{
	struct spi_device *spi = to_spi_device(dev);
	struct pcf2123_sysfs_reg *r;
	u8 txbuf[1], rxbuf[1];
	unsigned long reg;
	int ret;

	r = container_of(attr, struct pcf2123_sysfs_reg, attr);

	ret = kstrtoul(r->name, 16, &reg);
	if (ret)
		return ret;

	txbuf[0] = PCF2123_READ | reg;
	ret = spi_write_then_read(spi, txbuf, 1, rxbuf, 1);
	if (ret < 0)
		return -EIO;
	pcf2123_delay_trec();
	return sprintf(buffer, "0x%x\n", rxbuf[0]);
}
