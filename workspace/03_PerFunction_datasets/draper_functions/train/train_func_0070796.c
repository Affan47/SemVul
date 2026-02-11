vf610_adc_reg_access(struct iio_dev *indio_dev,
			unsigned reg, unsigned writeval,
			unsigned *readval)
{
	struct vf610_adc *info = iio_priv(indio_dev);

	if ((readval == NULL) ||
		((reg % 4) || (reg > VF610_REG_ADC_PCTL)))
		return -EINVAL;

	*readval = readl(info->regs + reg);

	return 0;
}
