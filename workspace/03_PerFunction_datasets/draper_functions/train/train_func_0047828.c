e1000e_phy_hw_reset_ich8lan(struct e1000_hw *hw)
{
	s32 ret_val = E1000_SUCCESS;
	u16 reg;

	ret_val = e1000e_phy_hw_reset_generic(hw);
	if (ret_val)
		goto out;


	msleep(10);

	if (hw->mac.type == e1000_pchlan) {
		ret_val = e1000e_hv_phy_workarounds_ich8lan(hw);
		if (ret_val)
			goto out;
	}


	if (hw->mac.type == e1000_pchlan)
		e1e_rphy(hw, BM_WUC, &reg);


	ret_val = e1000e_sw_lcd_config_ich8lan(hw);
	if (ret_val)
		goto out;


	if (hw->mac.type == e1000_pchlan)
		ret_val = e1000e_oem_bits_config_ich8lan(hw, true);

out:
	return ret_val;
}
