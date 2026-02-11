wm8978_enum_mclk(unsigned int f_out, unsigned int f_mclk,
			    unsigned int *f_pllout)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(mclk_numerator); i++) {
		unsigned int f_pllout_x4 = 4 * f_out * mclk_numerator[i] /
			mclk_denominator[i];
		if (3 * f_mclk <= f_pllout_x4 && f_pllout_x4 < 13 * f_mclk) {
			*f_pllout = f_pllout_x4 / 4;
			return i;
		}
	}

	return -EINVAL;
}
