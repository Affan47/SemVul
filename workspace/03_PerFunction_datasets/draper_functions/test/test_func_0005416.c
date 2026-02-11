itd1000_set_vco(struct itd1000_state *state, u32 freq_khz)
{
	u8 i;
	u8 gvbb_i2c     = itd1000_read_reg(state, GVBB_I2C) & 0xbf;
	u8 vco_chp1_i2c = itd1000_read_reg(state, VCO_CHP1_I2C) & 0x0f;
	u8 adcout;


	itd1000_write_reg(state, GVBB_I2C, gvbb_i2c | (1 << 6));

	for (i = 0; i < ARRAY_SIZE(itd1000_vcorg); i++) {
		if (freq_khz < itd1000_vcorg[i].fmax_rg) {
			itd1000_write_reg(state, VCO_CHP1_I2C, vco_chp1_i2c | (itd1000_vcorg[i].vcorg << 4));
			msleep(1);

			adcout = itd1000_read_reg(state, PLLLOCK) & 0x0f;

			itd_dbg("VCO: %dkHz: %d -> ADCOUT: %d %02x\n", freq_khz, itd1000_vcorg[i].vcorg, adcout, vco_chp1_i2c);

			if (adcout > 13) {
				if (!(itd1000_vcorg[i].vcorg == 7 || itd1000_vcorg[i].vcorg == 15))
					itd1000_write_reg(state, VCO_CHP1_I2C, vco_chp1_i2c | ((itd1000_vcorg[i].vcorg + 1) << 4));
			} else if (adcout < 2) {
				if (!(itd1000_vcorg[i].vcorg == 1 || itd1000_vcorg[i].vcorg == 9))
					itd1000_write_reg(state, VCO_CHP1_I2C, vco_chp1_i2c | ((itd1000_vcorg[i].vcorg - 1) << 4));
			}
			break;
		}
	}
}
