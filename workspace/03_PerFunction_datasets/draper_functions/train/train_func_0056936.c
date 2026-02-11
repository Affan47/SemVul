igb_write_mbx_pf(struct e1000_hw *hw, u32 *msg, u16 size,
			    u16 vf_number)
{
	s32 ret_val;
	u16 i;


	ret_val = igb_obtain_mbx_lock_pf(hw, vf_number);
	if (ret_val)
		goto out_no_write;


	igb_check_for_msg_pf(hw, vf_number);
	igb_check_for_ack_pf(hw, vf_number);


	for (i = 0; i < size; i++)
		array_wr32(E1000_VMBMEM(vf_number), i, msg[i]);


	wr32(E1000_P2VMAILBOX(vf_number), E1000_P2VMAILBOX_STS);


	hw->mbx.stats.msgs_tx++;

out_no_write:
	return ret_val;

}
