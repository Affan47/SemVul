spu_set_bus_mode(struct if_spi_card *card, u16 mode)
{
	int err = 0;
	u16 rval;

	err = spu_write_u16(card, IF_SPI_SPU_BUS_MODE_REG, mode);
	if (err)
		return err;

	err = spu_read_u16(card, IF_SPI_SPU_BUS_MODE_REG, &rval);
	if (err)
		return err;
	if ((rval & 0xF) != mode) {
		pr_err("Can't read bus mode register\n");
		return -EIO;
	}
	return 0;
}
