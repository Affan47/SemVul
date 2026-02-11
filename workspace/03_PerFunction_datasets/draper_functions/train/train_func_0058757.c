ics5342_set_freq(struct dac_info *info, int channel, u32 freq)
{
	u16 m, n, r;


	int rv = svga_compute_pll((DAC_PAR(info)->mode == DAC_PSEUDO8_16)
				  ? &ics5342_pll_pd4 : &ics5342_pll,
				  freq, &m, &n, &r, 0);

	if (rv < 0) {
		return -EINVAL;
	} else {
		u8 code[6] = {4, 3, 5, m-2, 5, (n-2) | (r << 5)};
		dac_write_regs(info, code, 3);
		return 0;
	}
}
