igb_read_pba_num_generic(struct e1000_hw *hw, u32 *pba_num)
{
	s32  ret_val;
	u16 nvm_data;

	DEBUGFUNC("igb_read_pba_num_generic");

	ret_val = hw->nvm.ops.read(hw, NVM_PBA_OFFSET_0, 1, &nvm_data);
	if (ret_val) {
		DEBUGOUT("NVM Read Error\n");
		goto out;
	}
	*pba_num = (u32)(nvm_data << 16);

	ret_val = hw->nvm.ops.read(hw, NVM_PBA_OFFSET_1, 1, &nvm_data);
	if (ret_val) {
		DEBUGOUT("NVM Read Error\n");
		goto out;
	}
	*pba_num |= nvm_data;

out:
	return ret_val;
}
