e1000_validate_mdi_setting(struct e1000_hw *hw)
{
	if (hw->mac.ops.validate_mdi_setting)
		return hw->mac.ops.validate_mdi_setting(hw);

	return E1000_SUCCESS;
}
