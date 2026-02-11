brcms_c_rate_hwrs_filter_sort_validate(struct brcms_c_rateset *rs,
				   const struct brcms_c_rateset *hw_rs,
				   bool check_brate, u8 txstreams)
{
	u8 rateset[BRCM_MAXRATE + 1];
	u8 r;
	uint count;
	uint i;

	memset(rateset, 0, sizeof(rateset));
	count = rs->count;

	for (i = 0; i < count; i++) {

		r = (int)rs->rates[i] & BRCMS_RATE_MASK;
		if ((r > BRCM_MAXRATE) || (rate_info[r] == 0))
			continue;
		rateset[r] = rs->rates[i];
	}


	count = 0;
	for (i = 0; i < hw_rs->count; i++) {
		r = hw_rs->rates[i] & BRCMS_RATE_MASK;
		if (rateset[r])
			rs->rates[count++] = rateset[r];
	}

	rs->count = count;


	for (i = 0; i < MCSSET_LEN; i++)
		rs->mcs[i] = (rs->mcs[i] & hw_rs->mcs[i]);

	if (brcms_c_rateset_valid(rs, check_brate))
		return true;
	else
		return false;
}
