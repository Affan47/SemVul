ade7854_set_irq(struct device *dev, bool enable)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ade7854_state *st = iio_priv(indio_dev);

	int ret;
	u32 irqen;

	ret = st->read_reg_32(dev, ADE7854_MASK0, &irqen);
	if (ret)
		goto error_ret;

	if (enable)
		irqen |= BIT(17);

	else
		irqen &= ~BIT(17);

	ret = st->write_reg_32(dev, ADE7854_MASK0, irqen);
	if (ret)
		goto error_ret;

error_ret:
	return ret;
}
