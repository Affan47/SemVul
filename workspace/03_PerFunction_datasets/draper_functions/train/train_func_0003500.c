ade7854_i2c_read_reg_32(struct device *dev,
				   u16 reg_address,
				   u32 *val)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ade7854_state *st = iio_priv(indio_dev);
	int ret;

	mutex_lock(&st->buf_lock);
	st->tx[0] = (reg_address >> 8) & 0xFF;
	st->tx[1] = reg_address & 0xFF;

	ret = i2c_master_send(st->i2c, st->tx, 2);
	if (ret)
		goto out;

	ret = i2c_master_recv(st->i2c, st->rx, 3);
	if (ret)
		goto out;

	*val = (st->rx[0] << 24) | (st->rx[1] << 16) |
		(st->rx[2] << 8) | st->rx[3];
out:
	mutex_unlock(&st->buf_lock);
	return ret;
}
