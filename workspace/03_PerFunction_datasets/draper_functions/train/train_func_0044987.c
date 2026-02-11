ixgbe_identify_module_generic(struct ixgbe_hw *hw)
{
	switch (hw->mac.ops.get_media_type(hw)) {
	case ixgbe_media_type_fiber:
		return ixgbe_identify_sfp_module_generic(hw);
	case ixgbe_media_type_fiber_qsfp:
		return ixgbe_identify_qsfp_module_generic(hw);
	default:
		hw->phy.sfp_type = ixgbe_sfp_type_not_present;
		return IXGBE_ERR_SFP_NOT_PRESENT;
	}

	return IXGBE_ERR_SFP_NOT_PRESENT;
}
