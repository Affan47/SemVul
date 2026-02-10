brcms_c_ampdu_shm_upd(struct ampdu_info *ampdu)
{
	struct brcms_c_info *wlc = ampdu->wlc;


	if ((ampdu->rx_factor & IEEE80211_HT_AMPDU_PARM_FACTOR) ==
	    IEEE80211_HT_MAX_AMPDU_64K) {
		brcms_b_write_shm(wlc->hw, M_MIMO_MAXSYM, MIMO_MAXSYM_MAX);
		brcms_b_write_shm(wlc->hw, M_WATCHDOG_8TU, WATCHDOG_8TU_MAX);
	} else {
		brcms_b_write_shm(wlc->hw, M_MIMO_MAXSYM, MIMO_MAXSYM_DEF);
		brcms_b_write_shm(wlc->hw, M_WATCHDOG_8TU, WATCHDOG_8TU_DEF);
	}
}
