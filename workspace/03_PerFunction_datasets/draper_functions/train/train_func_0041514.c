iwl_mvm_mac_ctxt_set_tim(struct iwl_mvm *mvm,
				     struct iwl_mac_beacon_cmd *beacon_cmd,
				     u8 *beacon, u32 frame_size)
{
	u32 tim_idx;
	struct ieee80211_mgmt *mgmt = (struct ieee80211_mgmt *)beacon;


	tim_idx = mgmt->u.beacon.variable - beacon;


	while ((tim_idx < (frame_size - 2)) &&
			(beacon[tim_idx] != WLAN_EID_TIM))
		tim_idx += beacon[tim_idx+1] + 2;


	if ((tim_idx < (frame_size - 1)) && (beacon[tim_idx] == WLAN_EID_TIM)) {
		beacon_cmd->tim_idx = cpu_to_le32(tim_idx);
		beacon_cmd->tim_size = cpu_to_le32((u32)beacon[tim_idx+1]);
	} else {
		IWL_WARN(mvm, "Unable to find TIM Element in beacon\n");
	}
}
