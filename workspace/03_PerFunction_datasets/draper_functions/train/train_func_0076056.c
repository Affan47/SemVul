adis16400_initial_setup(struct iio_dev *indio_dev)
{
	struct adis16400_state *st = iio_priv(indio_dev);
	uint16_t prod_id, smp_prd;
	unsigned int device_id;
	int ret;


	if (st->variant->flags & ADIS16400_HAS_SLOW_MODE)
		st->adis.spi->max_speed_hz = ADIS16400_SPI_SLOW;
	else
		st->adis.spi->max_speed_hz = ADIS16400_SPI_FAST;
	st->adis.spi->mode = SPI_MODE_3;
	spi_setup(st->adis.spi);

	ret = adis_initial_startup(&st->adis);
	if (ret)
		return ret;

	if (st->variant->flags & ADIS16400_HAS_PROD_ID) {
		ret = adis_read_reg_16(&st->adis,
						ADIS16400_PRODUCT_ID, &prod_id);
		if (ret)
			goto err_ret;

		sscanf(indio_dev->name, "adis%u\n", &device_id);

		if (prod_id != device_id)
			dev_warn(&indio_dev->dev, "Device ID(%u) and product ID(%u) do not match.",
					device_id, prod_id);

		dev_info(&indio_dev->dev, "%s: prod_id 0x%04x at CS%d (irq %d)\n",
			indio_dev->name, prod_id,
			st->adis.spi->chip_select, st->adis.spi->irq);
	}

	if (st->variant->flags & ADIS16400_HAS_SLOW_MODE) {
		ret = adis_read_reg_16(&st->adis, ADIS16400_SMPL_PRD, &smp_prd);
		if (ret)
			goto err_ret;

		if ((smp_prd & ADIS16400_SMPL_PRD_DIV_MASK) < 0x0A) {
			st->adis.spi->max_speed_hz = ADIS16400_SPI_FAST;
			spi_setup(st->adis.spi);
		}
	}

err_ret:
	return ret;
}
