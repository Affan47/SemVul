brcms_c_stf_stbc_rx_set(struct brcms_c_info *wlc, s32 int_val)
{
	if ((int_val != HT_CAP_RX_STBC_NO)
	    && (int_val != HT_CAP_RX_STBC_ONE_STREAM))
		return false;

	if (BRCMS_STF_SS_STBC_RX(wlc)) {
		if ((int_val != HT_CAP_RX_STBC_NO)
		    && (wlc->stf->rxstreams == 1))
			return false;
	}

	brcms_c_stf_stbc_rx_ht_update(wlc, int_val);
	return true;
}
