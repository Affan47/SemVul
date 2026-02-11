isehb (uae_u16 bplcon0, uae_u16 bplcon2)
{
	bool bplehb;
	if (currprefs.chipset_mask & CSMASK_AGA)
		bplehb = (bplcon0 & 0x7010) == 0x6000;
	else if (currprefs.chipset_mask & CSMASK_ECS_DENISE)
		bplehb = ((bplcon0 & 0xFC00) == 0x6000 || (bplcon0 & 0xFC00) == 0x7000);
	else
		bplehb = ((bplcon0 & 0xFC00) == 0x6000 || (bplcon0 & 0xFC00) == 0x7000) && !currprefs.cs_denisenoehb;
	return bplehb;
}
