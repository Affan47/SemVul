BLTSIZH (int hpos, uae_u16 v)
{
	if (! (currprefs.chipset_mask & CSMASK_ECS_AGNUS))
		return;
	maybe_blit (hpos, 0);
	blt_info.hblitsize = v & 0x7FF;
	if (!blt_info.vblitsize)
		blt_info.vblitsize = 0x8000;
	if (!blt_info.hblitsize)
		blt_info.hblitsize = 0x0800;
	do_blitter (hpos, copper_access);
}
