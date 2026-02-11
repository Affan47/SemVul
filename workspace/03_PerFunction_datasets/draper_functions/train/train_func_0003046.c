e1000e_access_phy_debug_regs_hv(struct e1000_hw *hw, u32 offset,
                                          u16 *data, bool read)
{
	s32 ret_val;
	u32 addr_reg = 0;
	u32 data_reg = 0;


	addr_reg = (hw->phy.type == e1000_phy_82578) ?
	           I82578_ADDR_REG : I82577_ADDR_REG;
	data_reg = addr_reg + 1;


	hw->phy.addr = 2;


	ret_val = e1000e_write_phy_reg_mdic(hw, addr_reg, (u16)offset & 0x3F);
	if (ret_val) {
		e_dbg("Could not write PHY the HV address register\n");
		goto out;
	}


	if (read)
		ret_val = e1000e_read_phy_reg_mdic(hw, data_reg, data);
	else
		ret_val = e1000e_write_phy_reg_mdic(hw, data_reg, *data);

	if (ret_val) {
		e_dbg("Could not read data value from HV data register\n");
		goto out;
	}

out:
	return ret_val;
}
