b43_nphy_tables_init_rev0(struct b43_wldev *dev)
{

	if (dev->phy.do_full_init) {
		ntab_upload(dev, B43_NTAB_FRAMESTRUCT, b43_ntab_framestruct);
		ntab_upload(dev, B43_NTAB_FRAMELT, b43_ntab_framelookup);
		ntab_upload(dev, B43_NTAB_TMAP, b43_ntab_tmap);
		ntab_upload(dev, B43_NTAB_TDTRN, b43_ntab_tdtrn);
		ntab_upload(dev, B43_NTAB_INTLEVEL, b43_ntab_intlevel);
		ntab_upload(dev, B43_NTAB_PILOT, b43_ntab_pilot);
		ntab_upload(dev, B43_NTAB_TDI20A0, b43_ntab_tdi20a0);
		ntab_upload(dev, B43_NTAB_TDI20A1, b43_ntab_tdi20a1);
		ntab_upload(dev, B43_NTAB_TDI40A0, b43_ntab_tdi40a0);
		ntab_upload(dev, B43_NTAB_TDI40A1, b43_ntab_tdi40a1);
		ntab_upload(dev, B43_NTAB_CHANEST, b43_ntab_channelest);
		ntab_upload(dev, B43_NTAB_MCS, b43_ntab_mcs);
		ntab_upload(dev, B43_NTAB_NOISEVAR10, b43_ntab_noisevar10);
		ntab_upload(dev, B43_NTAB_NOISEVAR11, b43_ntab_noisevar11);
	}


	ntab_upload(dev, B43_NTAB_BDI, b43_ntab_bdi);
	ntab_upload(dev, B43_NTAB_PILOTLT, b43_ntab_pilotlt);
	ntab_upload(dev, B43_NTAB_C0_GAINCTL, b43_ntab_gainctl0);
	ntab_upload(dev, B43_NTAB_C1_GAINCTL, b43_ntab_gainctl1);
	ntab_upload(dev, B43_NTAB_C0_ESTPLT, b43_ntab_estimatepowerlt0);
	ntab_upload(dev, B43_NTAB_C1_ESTPLT, b43_ntab_estimatepowerlt1);
	ntab_upload(dev, B43_NTAB_C0_ADJPLT, b43_ntab_adjustpower0);
	ntab_upload(dev, B43_NTAB_C1_ADJPLT, b43_ntab_adjustpower1);
	ntab_upload(dev, B43_NTAB_C0_IQLT, b43_ntab_iqlt0);
	ntab_upload(dev, B43_NTAB_C1_IQLT, b43_ntab_iqlt1);
	ntab_upload(dev, B43_NTAB_C0_LOFEEDTH, b43_ntab_loftlt0);
	ntab_upload(dev, B43_NTAB_C1_LOFEEDTH, b43_ntab_loftlt1);
}
