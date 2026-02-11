e1000_write_mbx_vf(struct e1000_hw *hw, u32 *msg, u16 size)
{
	s32 err;
	u16 i;


	err = e1000_obtain_mbx_lock_vf(hw);
	if (err)
		goto out_no_write;


	e1000_check_for_ack_vf(hw);
	e1000_check_for_msg_vf(hw);


	for (i = 0; i < size; i++)
		array_ew32(VMBMEM(0), i, msg[i]);


	hw->mbx.stats.msgs_tx++;


	ew32(V2PMAILBOX(0), E1000_V2PMAILBOX_REQ);

out_no_write:
	return err;
}
