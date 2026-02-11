e1000e_update_phy_stats(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	s32 ret_val;
	u16 phy_data;

	ret_val = hw->phy.ops.acquire(hw);
	if (ret_val)
		return;


	hw->phy.addr = 1;
	ret_val = e1000e_read_phy_reg_mdic(hw, IGP01E1000_PHY_PAGE_SELECT,
					   &phy_data);
	if (ret_val)
		goto release;
	if (phy_data != (HV_STATS_PAGE << IGP_PAGE_SHIFT)) {
		ret_val = hw->phy.ops.set_page(hw,
					       HV_STATS_PAGE << IGP_PAGE_SHIFT);
		if (ret_val)
			goto release;
	}


	hw->phy.ops.read_reg_page(hw, HV_SCC_UPPER, &phy_data);
	ret_val = hw->phy.ops.read_reg_page(hw, HV_SCC_LOWER, &phy_data);
	if (!ret_val)
		adapter->stats.scc += phy_data;


	hw->phy.ops.read_reg_page(hw, HV_ECOL_UPPER, &phy_data);
	ret_val = hw->phy.ops.read_reg_page(hw, HV_ECOL_LOWER, &phy_data);
	if (!ret_val)
		adapter->stats.ecol += phy_data;


	hw->phy.ops.read_reg_page(hw, HV_MCC_UPPER, &phy_data);
	ret_val = hw->phy.ops.read_reg_page(hw, HV_MCC_LOWER, &phy_data);
	if (!ret_val)
		adapter->stats.mcc += phy_data;


	hw->phy.ops.read_reg_page(hw, HV_LATECOL_UPPER, &phy_data);
	ret_val = hw->phy.ops.read_reg_page(hw, HV_LATECOL_LOWER, &phy_data);
	if (!ret_val)
		adapter->stats.latecol += phy_data;


	hw->phy.ops.read_reg_page(hw, HV_COLC_UPPER, &phy_data);
	ret_val = hw->phy.ops.read_reg_page(hw, HV_COLC_LOWER, &phy_data);
	if (!ret_val)
		hw->mac.collision_delta = phy_data;


	hw->phy.ops.read_reg_page(hw, HV_DC_UPPER, &phy_data);
	ret_val = hw->phy.ops.read_reg_page(hw, HV_DC_LOWER, &phy_data);
	if (!ret_val)
		adapter->stats.dc += phy_data;


	hw->phy.ops.read_reg_page(hw, HV_TNCRS_UPPER, &phy_data);
	ret_val = hw->phy.ops.read_reg_page(hw, HV_TNCRS_LOWER, &phy_data);
	if (!ret_val)
		adapter->stats.tncrs += phy_data;

release:
	hw->phy.ops.release(hw);
}
