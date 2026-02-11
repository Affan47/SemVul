e1000_read_mbx_vf(struct e1000_hw *hw, u32 *msg, u16 size)
{
	s32 err;
	u16 i;


	err = e1000_obtain_mbx_lock_vf(hw);
	if (err)
		goto out_no_read;


	for (i = 0; i < size; i++)
		msg[i] = array_er32(VMBMEM(0), i);


	ew32(V2PMAILBOX(0), E1000_V2PMAILBOX_ACK);


	hw->mbx.stats.msgs_rx++;

out_no_read:
	return err;
}
