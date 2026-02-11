e1000_access_phy_wakeup_reg_bm(struct e1000_hw *hw, u32 offset,
					  u16 *data, bool read, bool page_set)
{
	s32 ret_val;
	u16 reg = BM_PHY_REG_NUM(offset);
	u16 page = BM_PHY_REG_PAGE(offset);
	u16 phy_reg = 0;


	if ((hw->mac.type == e1000_pchlan) &&
	    (!(er32(PHY_CTRL) & E1000_PHY_CTRL_GBE_DISABLE)))
		e_dbg("Attempting to access page %d while gig enabled.\n",
		      page);

	if (!page_set) {

		ret_val = e1000_enable_phy_wakeup_reg_access_bm(hw, &phy_reg);
		if (ret_val) {
			e_dbg("Could not enable PHY wakeup reg access\n");
			return ret_val;
		}
	}

	e_dbg("Accessing PHY page %d reg 0x%x\n", page, reg);


	ret_val = e1000e_write_phy_reg_mdic(hw, BM_WUC_ADDRESS_OPCODE, reg);
	if (ret_val) {
		e_dbg("Could not write address opcode to page %d\n", page);
		return ret_val;
	}

	if (read) {

		ret_val = e1000e_read_phy_reg_mdic(hw, BM_WUC_DATA_OPCODE,
						   data);
	} else {

		ret_val = e1000e_write_phy_reg_mdic(hw, BM_WUC_DATA_OPCODE,
						    *data);
	}

	if (ret_val) {
		e_dbg("Could not access PHY reg %d.%d\n", page, reg);
		return ret_val;
	}

	if (!page_set)
		ret_val = e1000_disable_phy_wakeup_reg_access_bm(hw, &phy_reg);

	return ret_val;
}
