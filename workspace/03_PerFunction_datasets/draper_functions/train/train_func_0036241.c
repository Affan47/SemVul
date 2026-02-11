b43_wa_fft(struct b43_wldev *dev)
{
	int i;

	if (dev->phy.type == B43_PHYTYPE_A)
		for (i = 0; i < B43_TAB_FINEFREQA_SIZE; i++)
			b43_ofdmtab_write16(dev, B43_OFDMTAB_DACRFPABB, i, b43_tab_finefreqa[i]);
	else
		for (i = 0; i < B43_TAB_FINEFREQG_SIZE; i++)
			b43_ofdmtab_write16(dev, B43_OFDMTAB_DACRFPABB, i, b43_tab_finefreqg[i]);
}
