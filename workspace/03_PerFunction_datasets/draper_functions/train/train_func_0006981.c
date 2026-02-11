igb_rcv_ack_from_vf(struct igb_adapter *adapter, u32 vf)
{
	struct e1000_hw *hw = &adapter->hw;
	struct vf_data_storage *vf_data = &adapter->vf_data[vf];
	u32 msg = E1000_VT_MSGTYPE_NACK;


	if (!(vf_data->flags & IGB_VF_FLAG_CTS) &&
	    time_after(jiffies, vf_data->last_nack + (2 * HZ))) {
		igb_write_mbx(hw, &msg, 1, vf);
		vf_data->last_nack = jiffies;
	}
}
