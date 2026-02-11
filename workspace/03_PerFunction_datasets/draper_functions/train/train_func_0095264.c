linetoscr_16_shrink1_sh (int spix, int dpix, int stoppos, int spr)
{
	uae_u16 *buf = (uae_u16 *) xlinebuffer;

	while (dpix < stoppos) {
		uae_u16 spix_val1, spix_val2;
		uae_u16 v;
		int off;
		spix_val1 = pixdata.apixels[spix++];
		spix_val2 = pixdata.apixels[spix++];
		off = ((spix_val2 & 3) * 4) + (spix_val1 & 3) + ((spix_val1 | spix_val2) & 16);
		v = (colors_for_drawing.color_regs_ecs[off] & 0xccc) << 0;
		v |= v >> 2;
		PUTBPIX(shsprite (dpix, spix_val1, xcolors[v], spr));
		dpix++;
	}
	return spix;
}
