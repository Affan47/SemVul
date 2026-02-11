ath5k_rx_start(struct ath5k_hw *ah)
{
	struct ath_common *common = ath5k_hw_common(ah);
	struct ath5k_buf *bf;
	int ret;

	common->rx_bufsize = roundup(IEEE80211_MAX_FRAME_LEN, common->cachelsz);

	ATH5K_DBG(ah, ATH5K_DEBUG_RESET, "cachelsz %u rx_bufsize %u\n",
		  common->cachelsz, common->rx_bufsize);

	spin_lock_bh(&ah->rxbuflock);
	ah->rxlink = NULL;
	list_for_each_entry(bf, &ah->rxbuf, list) {
		ret = ath5k_rxbuf_setup(ah, bf);
		if (ret != 0) {
			spin_unlock_bh(&ah->rxbuflock);
			goto err;
		}
	}
	bf = list_first_entry(&ah->rxbuf, struct ath5k_buf, list);
	ath5k_hw_set_rxdp(ah, bf->daddr);
	spin_unlock_bh(&ah->rxbuflock);

	ath5k_hw_start_rx_dma(ah);
	ath5k_update_bssid_mask_and_opmode(ah, NULL);
	ath5k_hw_start_rx_pcu(ah);

	return 0;
err:
	return ret;
}
