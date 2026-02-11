twi_set_speed(Twi *p_twi, uint32_t ul_speed, uint32_t ul_mck)
{
	uint32_t ckdiv = 0;
	uint32_t c_lh_div;

	if (ul_speed > I2C_FAST_MODE_SPEED) {
		return FAIL;
	}

	c_lh_div = ul_mck / (ul_speed * TWI_CLK_DIVIDER) - TWI_CLK_CALC_ARGU;


	while ((c_lh_div > TWI_CLK_DIV_MAX) && (ckdiv < TWI_CLK_DIV_MIN)) {

		ckdiv++;

		c_lh_div /= TWI_CLK_DIVIDER;
	}


	p_twi->TWI_CWGR =
			TWI_CWGR_CLDIV(c_lh_div) | TWI_CWGR_CHDIV(c_lh_div) |
			TWI_CWGR_CKDIV(ckdiv);

	return PASS;
}
