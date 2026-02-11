brcms_c_set_nmode(struct brcms_c_info *wlc)
{
	uint i;
	s32 nmode = AUTO;

	if (wlc->stf->txstreams == WL_11N_3x3)
		nmode = WL_11N_3x3;
	else
		nmode = WL_11N_2x2;


	brcms_c_set_gmode(wlc, GMODE_AUTO, true);
	if (nmode == WL_11N_3x3)
		wlc->pub->_n_enab = SUPPORT_HT;
	else
		wlc->pub->_n_enab = SUPPORT_11N;
	wlc->default_bss->flags |= BRCMS_BSS_HT;

	brcms_c_rateset_mcs_build(&wlc->default_bss->rateset,
			      wlc->stf->txstreams);
	for (i = 0; i < wlc->pub->_nbands; i++)
		memcpy(wlc->bandstate[i]->hw_rateset.mcs,
		       wlc->default_bss->rateset.mcs, MCSSET_LEN);

	return 0;
}
