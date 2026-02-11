ar9003_mci_sync_bt_state(struct ath_hw *ah)
{
	struct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 cur_bt_state;

	cur_bt_state = ar9003_mci_state(ah, MCI_STATE_REMOTE_SLEEP);

	if (mci->bt_state != cur_bt_state)
		mci->bt_state = cur_bt_state;

	if (mci->bt_state != MCI_BT_SLEEP) {

		ar9003_mci_send_coex_version_query(ah, true);
		ar9003_mci_send_coex_wlan_channels(ah, true);

		if (mci->unhalt_bt_gpm == true)
			ar9003_mci_send_coex_halt_bt_gpm(ah, false, true);
	}
}
