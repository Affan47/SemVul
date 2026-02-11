fm10k_update_mc_addr_vf(struct fm10k_hw *hw, u16 glort,
				   const u8 *mac, u16 vid, bool add)
{
	struct fm10k_mbx_info *mbx = &hw->mbx;
	u32 msg[7];


	if (vid >= FM10K_VLAN_TABLE_VID_MAX)
		return FM10K_ERR_PARAM;


	if (!is_multicast_ether_addr(mac))
		return FM10K_ERR_PARAM;


	if (!add)
		vid |= FM10K_VLAN_CLEAR;


	fm10k_tlv_msg_init(msg, FM10K_VF_MSG_ID_MAC_VLAN);
	fm10k_tlv_attr_put_mac_vlan(msg, FM10K_MAC_VLAN_MSG_MULTICAST,
				    mac, vid);


	return mbx->ops.enqueue_tx(hw, mbx, msg);
}
