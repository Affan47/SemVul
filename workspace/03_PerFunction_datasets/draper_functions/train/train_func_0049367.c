BPLCON1 (int hpos, uae_u16 v)
{
	if (!(currprefs.chipset_mask & CSMASK_AGA))
		v &= 0xff;
	if (bplcon1 == v)
		return;
	ddf_change = vpos;
	decide_line (hpos);
	decide_fetch (hpos);
	bplcon1_hpos = hpos;
	bplcon1 = v;
}
