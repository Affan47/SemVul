dib8000_set_dds(struct dib8000_state *state, s32 offset_khz)
{
	s16 unit_khz_dds_val;
	u32 abs_offset_khz = ABS(offset_khz);
	u32 dds = state->cfg.pll->ifreq & 0x1ffffff;
	u8 invert = !!(state->cfg.pll->ifreq & (1 << 25));
	u8 ratio;

	if (state->revision == 0x8090) {
		ratio = 4;
		unit_khz_dds_val = (1<<26) / (dib8000_read32(state, 23) / 1000);
		if (offset_khz < 0)
			dds = (1 << 26) - (abs_offset_khz * unit_khz_dds_val);
		else
			dds = (abs_offset_khz * unit_khz_dds_val);

		if (invert)
			dds = (1<<26) - dds;
	} else {
		ratio = 2;
		unit_khz_dds_val = (u16) (67108864 / state->cfg.pll->internal);

		if (offset_khz < 0)
			unit_khz_dds_val *= -1;


		if (invert)
			dds -= abs_offset_khz * unit_khz_dds_val;
		else
			dds += abs_offset_khz * unit_khz_dds_val;
	}

	dprintk("setting a DDS frequency offset of %c%dkHz", invert ? '-' : ' ', dds / unit_khz_dds_val);

	if (abs_offset_khz <= (state->cfg.pll->internal / ratio)) {

		dib8000_write_word(state, 26, invert);
		dib8000_write_word(state, 27, (u16)(dds >> 16) & 0x1ff);
		dib8000_write_word(state, 28, (u16)(dds & 0xffff));
	}
}
