bh1770_lux_raw_to_adjusted(struct bh1770_chip *chip, u16 raw)
{
	u32 lux;
	lux = ((u32)raw * chip->lux_corr) / BH1770_LUX_CORR_SCALE;
	return min(lux, (u32)BH1770_LUX_RANGE);
}
