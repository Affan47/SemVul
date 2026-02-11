brcms_c_set_internal_rateset(struct brcms_c_info *wlc,
			     struct brcms_c_rateset *rs_arg)
{
	struct brcms_c_rateset rs, new;
	uint bandunit;

	memcpy(&rs, rs_arg, sizeof(struct brcms_c_rateset));


	if ((rs.count == 0) || (rs.count > BRCMS_NUMRATES))
		return -EINVAL;


	bandunit = wlc->band->bandunit;
	memcpy(&new, &rs, sizeof(struct brcms_c_rateset));
	if (brcms_c_rate_hwrs_filter_sort_validate
	    (&new, &wlc->bandstate[bandunit]->hw_rateset, true,
	     wlc->stf->txstreams))
		goto good;


	if (brcms_is_mband_unlocked(wlc)) {
		bandunit = OTHERBANDUNIT(wlc);
		memcpy(&new, &rs, sizeof(struct brcms_c_rateset));
		if (brcms_c_rate_hwrs_filter_sort_validate(&new,
						       &wlc->
						       bandstate[bandunit]->
						       hw_rateset, true,
						       wlc->stf->txstreams))
			goto good;
	}

	return -EBADE;

 good:

	memcpy(&wlc->default_bss->rateset, &new,
	       sizeof(struct brcms_c_rateset));
	memcpy(&wlc->bandstate[bandunit]->defrateset, &new,
	       sizeof(struct brcms_c_rateset));
	return 0;
}
