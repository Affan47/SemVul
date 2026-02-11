fsl_spi_grlib_cs_control(struct spi_device *spi, bool on)
{
	struct mpc8xxx_spi *mpc8xxx_spi = spi_master_get_devdata(spi->master);
	struct fsl_spi_reg *reg_base = mpc8xxx_spi->reg_base;
	u32 slvsel;
	u16 cs = spi->chip_select;

	if (gpio_is_valid(spi->cs_gpio)) {
		gpio_set_value(spi->cs_gpio, on);
	} else if (cs < mpc8xxx_spi->native_chipselects) {
		slvsel = mpc8xxx_spi_read_reg(&reg_base->slvsel);
		slvsel = on ? (slvsel | (1 << cs)) : (slvsel & ~(1 << cs));
		mpc8xxx_spi_write_reg(&reg_base->slvsel, slvsel);
	}
}
