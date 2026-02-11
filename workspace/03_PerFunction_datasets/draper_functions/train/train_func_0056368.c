ad7879_spi_read(struct device *dev, u8 reg)
{
	struct spi_device *spi = to_spi_device(dev);
	u16 ret, dummy;

	return ad7879_spi_xfer(spi, AD7879_READCMD(reg), 1, &dummy, &ret) ? : ret;
}
