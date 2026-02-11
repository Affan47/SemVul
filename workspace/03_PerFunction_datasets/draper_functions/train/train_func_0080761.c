blitter_line (void)
{
	uae_u16 blitahold = (blinea & blt_info.bltafwm) >> blinea_shift;
	uae_u16 blitchold = blt_info.bltcdat;

	blt_info.bltbhold = (blineb & 1) ? 0xFFFF : 0;
	blitlinepixel = !blitsing || (blitsing && !blitonedot);
	blt_info.bltddat = blit_func (blitahold, blt_info.bltbhold, blitchold, bltcon0 & 0xFF);
	blitonedot++;
}
