brcms_c_detach_module(struct brcms_c_info *wlc)
{
	if (wlc->asi) {
		brcms_c_antsel_detach(wlc->asi);
		wlc->asi = NULL;
	}

	if (wlc->ampdu) {
		brcms_c_ampdu_detach(wlc->ampdu);
		wlc->ampdu = NULL;
	}

	brcms_c_stf_detach(wlc);
}
