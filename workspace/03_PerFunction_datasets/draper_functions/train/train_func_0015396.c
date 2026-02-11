lms283gf05_probe(struct spi_device *spi)
{
	struct lms283gf05_state *st;
	struct lms283gf05_pdata *pdata = dev_get_platdata(&spi->dev);
	struct lcd_device *ld;
	int ret = 0;

	if (pdata != NULL) {
		ret = devm_gpio_request_one(&spi->dev, pdata->reset_gpio,
				GPIOF_DIR_OUT | (!pdata->reset_inverted ?
				GPIOF_INIT_HIGH : GPIOF_INIT_LOW),
				"LMS285GF05 RESET");
		if (ret)
			return ret;
	}

	st = devm_kzalloc(&spi->dev, sizeof(struct lms283gf05_state),
				GFP_KERNEL);
	if (st == NULL)
		return -ENOMEM;

	ld = devm_lcd_device_register(&spi->dev, "lms283gf05", &spi->dev, st,
					&lms_ops);
	if (IS_ERR(ld))
		return PTR_ERR(ld);

	st->spi = spi;
	st->ld = ld;

	spi_set_drvdata(spi, st);


	if (pdata)
		lms283gf05_reset(pdata->reset_gpio, pdata->reset_inverted);
	lms283gf05_toggle(spi, disp_initseq, ARRAY_SIZE(disp_initseq));

	return 0;
}
