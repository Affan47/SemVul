brcms_c_beacon_write(struct brcms_c_info *wlc,
				 struct sk_buff *beacon, u16 tim_offset,
				 u16 dtim_period, bool bcn0, bool bcn1)
{
	size_t len;
	struct ieee80211_tx_info *tx_info;
	struct brcms_hardware *wlc_hw = wlc->hw;
	struct ieee80211_hw *ieee_hw = brcms_c_pub(wlc)->ieee_hw;


	tx_info = IEEE80211_SKB_CB(beacon);

	len = min_t(size_t, beacon->len, BCN_TMPL_LEN);
	wlc->bcn_rspec = ieee80211_get_tx_rate(ieee_hw, tx_info)->hw_value;

	brcms_c_compute_plcp(wlc, wlc->bcn_rspec,
			     len + FCS_LEN - D11_PHY_HDR_LEN, beacon->data);


	brcms_c_beacon_phytxctl_txant_upd(wlc, wlc->bcn_rspec);

	if (bcn0) {

		brcms_b_write_template_ram(wlc_hw, T_BCN0_TPL_BASE,
					    (len + 3) & ~3, beacon->data);


		brcms_b_write_shm(wlc_hw, M_BCN0_FRM_BYTESZ, (u16) len);
	}
	if (bcn1) {

		brcms_b_write_template_ram(wlc_hw, T_BCN1_TPL_BASE,
					    (len + 3) & ~3, beacon->data);


		brcms_b_write_shm(wlc_hw, M_BCN1_FRM_BYTESZ, (u16) len);
	}

	if (tim_offset != 0) {
		brcms_b_write_shm(wlc_hw, M_TIMBPOS_INBEACON,
				  tim_offset + D11B_PHY_HDR_LEN);
		brcms_b_write_shm(wlc_hw, M_DOT11_DTIMPERIOD, dtim_period);
	} else {
		brcms_b_write_shm(wlc_hw, M_TIMBPOS_INBEACON,
				  len + D11B_PHY_HDR_LEN);
		brcms_b_write_shm(wlc_hw, M_DOT11_DTIMPERIOD, 0);
	}
}
