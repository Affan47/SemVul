si514_get_muldiv(struct clk_si514 *data,
	struct clk_si514_muldiv *settings)
{
	int err;
	u8 reg[7];

	err = regmap_bulk_read(data->regmap, SI514_REG_M_FRAC1,
			reg, ARRAY_SIZE(reg));
	if (err)
		return err;

	settings->m_frac = reg[0] | reg[1] << 8 | reg[2] << 16 |
			   (reg[3] & 0x1F) << 24;
	settings->m_int = (reg[4] & 0x3f) << 3 | reg[3] >> 5;
	settings->ls_div_bits = (reg[6] >> 4) & 0x07;
	settings->hs_div = (reg[6] & 0x03) << 8 | reg[5];
	return 0;
}
