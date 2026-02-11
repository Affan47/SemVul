adis16130_spi_read(struct iio_dev *indio_dev, u8 reg_addr, u32 *val)
{
	int ret;
	struct adis16130_state *st = iio_priv(indio_dev);
	struct spi_transfer xfer = {
		.tx_buf = st->buf,
		.rx_buf = st->buf,
		.len = 4,
	};

	mutex_lock(&st->buf_lock);

	st->buf[0] = ADIS16130_CON_RD | reg_addr;
	st->buf[1] = st->buf[2] = st->buf[3] = 0;

	ret = spi_sync_transfer(st->us, &xfer, 1);
	if (ret == 0)
		*val = (st->buf[1] << 16) | (st->buf[2] << 8) | st->buf[3];
	mutex_unlock(&st->buf_lock);

	return ret;
}
