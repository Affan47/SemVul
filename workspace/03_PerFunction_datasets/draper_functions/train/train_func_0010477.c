brcms_c_set_shortslot_override(struct brcms_c_info *wlc, s8 sslot_override)
{
	wlc->shortslot_override = sslot_override;


	if (wlc->band->bandtype == BRCM_BAND_5G)
		return;

	if (wlc->pub->up && wlc->pub->associated) {

	} else if (wlc->pub->up) {

		brcms_c_switch_shortslot(wlc, false);
	} else {


		if (wlc->shortslot_override == BRCMS_SHORTSLOT_AUTO)
			wlc->shortslot = false;
		else
			wlc->shortslot =
			    (wlc->shortslot_override ==
			     BRCMS_SHORTSLOT_ON);
	}
}
