ar9003_mci_send_coex_wlan_channels(struct ath_hw *ah,
					       bool wait_done)
{
	struct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 *payload = &mci->wlan_channels[0];

	if (!mci->wlan_channels_update ||
	    (mci->bt_state == MCI_BT_SLEEP))
		return;

	MCI_GPM_SET_TYPE_OPCODE(payload, MCI_GPM_COEX_AGENT,
				MCI_GPM_COEX_WLAN_CHANNELS);
	ar9003_mci_send_message(ah, MCI_GPM, 0, payload, 16, wait_done, true);
	MCI_GPM_SET_TYPE_OPCODE(payload, 0xff, 0xff);
}
