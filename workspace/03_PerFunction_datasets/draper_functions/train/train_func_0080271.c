rspi_set_config_register(struct rspi_data *rspi, int access_size)
{
	int spbr;


	rspi_write8(rspi, rspi->sppcr, RSPI_SPPCR);


	spbr = DIV_ROUND_UP(clk_get_rate(rspi->clk),
			    2 * rspi->max_speed_hz) - 1;
	rspi_write8(rspi, clamp(spbr, 0, 255), RSPI_SPBR);


	rspi_write8(rspi, 0, RSPI_SPDCR);
	rspi->byte_access = 0;


	rspi_write8(rspi, 0x00, RSPI_SPCKD);
	rspi_write8(rspi, 0x00, RSPI_SSLND);
	rspi_write8(rspi, 0x00, RSPI_SPND);


	rspi_write8(rspi, 0x00, RSPI_SPCR2);


	rspi->spcmd |= SPCMD_SPB_8_TO_16(access_size);
	rspi_write16(rspi, rspi->spcmd, RSPI_SPCMD0);


	rspi_write8(rspi, SPCR_MSTR, RSPI_SPCR);

	return 0;
}
