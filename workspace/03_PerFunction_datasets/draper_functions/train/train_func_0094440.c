pxa2xx_ssp_get_clk_div(struct driver_data *drv_data,
					   int rate)
{
	struct chip_data *chip = drv_data->cur_chip;
	unsigned int clk_div;

	switch (drv_data->ssp_type) {
	case QUARK_X1000_SSP:
		clk_div = quark_x1000_get_clk_div(rate, &chip->dds_rate);
		break;
	default:
		clk_div = ssp_get_clk_div(drv_data, rate);
		break;
	}
	return clk_div << 8;
}
