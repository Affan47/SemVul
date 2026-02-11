ath9k_hw_btcoex_set_weight(struct ath_hw *ah,
				u32 bt_weight,
				u32 wlan_weight,
				enum ath_stomp_type stomp_type)
{
	struct ath_btcoex_hw *btcoex_hw = &ah->btcoex_hw;
	struct ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;
	u8 txprio_shift[] = { 24, 16, 16, 0 };
	bool concur_tx = (mci_hw->concur_tx && btcoex_hw->tx_prio[stomp_type]);
	const u32 *weight = ar9003_wlan_weights[stomp_type];
	int i;

	if (!AR_SREV_9300_20_OR_LATER(ah)) {
		btcoex_hw->bt_coex_weights =
			SM(bt_weight, AR_BTCOEX_BT_WGHT) |
			SM(wlan_weight, AR_BTCOEX_WL_WGHT);
		return;
	}

	if (AR_SREV_9462(ah) || AR_SREV_9565(ah)) {
		enum ath_stomp_type stype =
			((stomp_type == ATH_BTCOEX_STOMP_LOW) &&
			 btcoex_hw->mci.stomp_ftp) ?
			ATH_BTCOEX_STOMP_LOW_FTP : stomp_type;
		weight = mci_wlan_weights[stype];
	}

	for (i = 0; i < AR9300_NUM_WLAN_WEIGHTS; i++) {
		btcoex_hw->bt_weight[i] = AR9300_BT_WGHT;
		btcoex_hw->wlan_weight[i] = weight[i];
		if (concur_tx && i) {
			btcoex_hw->wlan_weight[i] &=
				~(0xff << txprio_shift[i-1]);
			btcoex_hw->wlan_weight[i] |=
				(btcoex_hw->tx_prio[stomp_type] <<
				 txprio_shift[i-1]);
		}
	}

	if (concur_tx) {
		btcoex_hw->wlan_weight[i-1] &= ~(0xff << txprio_shift[i-1]);
		btcoex_hw->wlan_weight[i-1] |= (btcoex_hw->tx_prio[stomp_type]
						      << txprio_shift[i-1]);
	}

}
