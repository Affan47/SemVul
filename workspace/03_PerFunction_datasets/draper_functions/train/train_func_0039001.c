e1000e_copper_link_setup_82577(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data;

	if (phy->reset_disable) {
		ret_val = E1000_SUCCESS;
		goto out;
	}


	ret_val = e1e_rphy(hw, I82577_CFG_REG, &phy_data);
	if (ret_val)
		goto out;

	phy_data |= I82577_CFG_ASSERT_CRS_ON_TX;


	phy_data |= I82577_CFG_ENABLE_DOWNSHIFT;

	ret_val = e1e_wphy(hw, I82577_CFG_REG, phy_data);

out:
	return ret_val;
}
