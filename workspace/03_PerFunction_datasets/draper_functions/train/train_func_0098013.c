max1027_set_trigger_state(struct iio_trigger *trig, bool state)
{
	struct iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	struct max1027_state *st = iio_priv(indio_dev);
	int ret;

	if (state) {

		st->reg = MAX1027_SETUP_REG | MAX1027_CKS_MODE0 |
			  MAX1027_REF_MODE2;
		ret = spi_write(st->spi, &st->reg, 1);
		if (ret < 0)
			return ret;


		st->reg = MAX1027_CONV_REG | MAX1027_CHAN(0) |
			  MAX1027_SCAN_N_M | MAX1027_TEMP;
		ret = spi_write(st->spi, &st->reg, 1);
		if (ret < 0)
			return ret;
	} else {

		st->reg = MAX1027_SETUP_REG | MAX1027_CKS_MODE2	|
			  MAX1027_REF_MODE2;
		ret = spi_write(st->spi, &st->reg, 1);
		if (ret < 0)
			return ret;
	}

	return 0;
}
