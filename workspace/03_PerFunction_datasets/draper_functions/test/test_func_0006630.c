tsl2550_calculate_lux(u8 ch0, u8 ch1)
{
	unsigned int lux;


	u16 c0 = count_lut[ch0];
	u16 c1 = count_lut[ch1];


	u8 r = 128;


	if (c1 <= c0)
		if (c0) {
			r = c1 * 128 / c0;


			lux = ((c0 - c1) * ratio_lut[r]) / 256;
		} else
			lux = 0;
	else
		return -EAGAIN;


	return lux > TSL2550_MAX_LUX ? TSL2550_MAX_LUX : lux;
}
