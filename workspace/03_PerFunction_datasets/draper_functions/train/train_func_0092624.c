weird_bitplane_fix (void)
{
	int i;
	int sh = lores_shift;
	uae_u8 *p = pixdata.apixels + pixels_offset;

	for (i = playfield_start >> sh; i < playfield_end >> sh; i++) {
		if (p[i] > 16)
			p[i] = 16;
	}
}
