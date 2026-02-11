brcms_b_detach(struct brcms_c_info *wlc)
{
	uint i;
	struct brcms_hw_band *band;
	struct brcms_hardware *wlc_hw = wlc->hw;

	brcms_b_detach_dmapio(wlc_hw);

	band = wlc_hw->band;
	for (i = 0; i < wlc_hw->_nbands; i++) {
		if (band->pi) {

			wlc_phy_detach(band->pi);
			band->pi = NULL;
		}
		band = wlc_hw->bandstate[OTHERBANDUNIT(wlc)];
	}


	kfree(wlc_hw->phy_sh);

	wlc_phy_shim_detach(wlc_hw->physhim);

	if (wlc_hw->sih) {
		ai_detach(wlc_hw->sih);
		wlc_hw->sih = NULL;
	}
}
