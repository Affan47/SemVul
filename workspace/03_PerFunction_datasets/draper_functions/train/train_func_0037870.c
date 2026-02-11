igbvf_check_for_ack_vf(struct e1000_hw *hw, u16 mbx_id __unused)
{
	s32 ret_val = -E1000_ERR_MBX;

	DEBUGFUNC("igbvf_check_for_ack_vf");

	if (!igbvf_check_for_bit_vf(hw, E1000_V2PMAILBOX_PFACK)) {
		ret_val = E1000_SUCCESS;
		hw->mbx.stats.acks++;
	}

	return ret_val;
}
