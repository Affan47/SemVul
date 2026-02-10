e1000_setup_link_82543(struct e1000_hw *hw)
{
	u32 ctrl_ext;
	s32  ret_val;
	u16 data;

	DEBUGFUNC("e1000_setup_link_82543");


	if (hw->mac.type == e1000_82543) {
		ret_val = hw->nvm.ops.read(hw, NVM_INIT_CONTROL2_REG, 1, &data);
		if (ret_val) {
			DEBUGOUT("NVM Read Error\n");
			ret_val = -E1000_ERR_NVM;
			goto out;
		}
		ctrl_ext = ((data & NVM_WORD0F_SWPDIO_EXT_MASK) <<
		            NVM_SWDPIO_EXT_SHIFT);
		E1000_WRITE_REG(hw, E1000_CTRL_EXT, ctrl_ext);
	}

	ret_val = e1000_setup_link_generic(hw);

out:
	return ret_val;
}
