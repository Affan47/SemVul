vf610_adc_buffer_postenable(struct iio_dev *indio_dev)
{
	struct vf610_adc *info = iio_priv(indio_dev);
	unsigned int channel;
	int ret;
	int val;

	ret = iio_triggered_buffer_postenable(indio_dev);
	if (ret)
		return ret;

	val = readl(info->regs + VF610_REG_ADC_GC);
	val |= VF610_ADC_ADCON;
	writel(val, info->regs + VF610_REG_ADC_GC);

	channel = find_first_bit(indio_dev->active_scan_mask,
						indio_dev->masklength);

	val = VF610_ADC_ADCHC(channel);
	val |= VF610_ADC_AIEN;

	writel(val, info->regs + VF610_REG_ADC_HC0);

	return 0;
}
