ad_sd_trigger_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct ad_sigma_delta *sigma_delta = iio_device_get_drvdata(indio_dev);
	unsigned int reg_size;
	uint8_t data[16];
	int ret;

	memset(data, 0x00, 16);

	reg_size = indio_dev->channels[0].scan_type.realbits +
			indio_dev->channels[0].scan_type.shift;
	reg_size = DIV_ROUND_UP(reg_size, 8);

	switch (reg_size) {
	case 4:
	case 2:
	case 1:
		ret = ad_sd_read_reg_raw(sigma_delta, AD_SD_REG_DATA,
			reg_size, &data[0]);
		break;
	case 3:


		ret = ad_sd_read_reg_raw(sigma_delta, AD_SD_REG_DATA,
			reg_size, &data[1]);
		break;
	}

	iio_push_to_buffers_with_timestamp(indio_dev, data, pf->timestamp);

	iio_trigger_notify_done(indio_dev->trig);
	sigma_delta->irq_dis = false;
	enable_irq(sigma_delta->spi->irq);

	return IRQ_HANDLED;
}
