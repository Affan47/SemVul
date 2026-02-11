ixgbe_init_phy_ops_X550em(struct ixgbe_hw *hw)
{
	struct ixgbe_phy_info *phy = &hw->phy;
	s32 ret_val;

	hw->mac.ops.set_lan_id(hw);

	if (hw->mac.ops.get_media_type(hw) == ixgbe_media_type_fiber) {
		phy->phy_semaphore_mask = IXGBE_GSSR_SHARED_I2C_SM;
		ixgbe_setup_mux_ctl(hw);


		phy->nw_mng_if_sel = IXGBE_READ_REG(hw, IXGBE_NW_MNG_IF_SEL);
	}


	ret_val = phy->ops.identify(hw);


	ixgbe_init_mac_link_ops_X550em(hw);
	if (phy->sfp_type != ixgbe_sfp_type_unknown)
		phy->ops.reset = NULL;


	switch (hw->phy.type) {
	case ixgbe_phy_x550em_kx4:
		phy->ops.setup_link = ixgbe_setup_kx4_x550em;
		phy->ops.read_reg = ixgbe_read_phy_reg_x550em;
		phy->ops.write_reg = ixgbe_write_phy_reg_x550em;
		break;
	case ixgbe_phy_x550em_kr:
		phy->ops.setup_link = ixgbe_setup_kr_x550em;
		phy->ops.read_reg = ixgbe_read_phy_reg_x550em;
		phy->ops.write_reg = ixgbe_write_phy_reg_x550em;
		break;
	case ixgbe_phy_x550em_ext_t:


		phy->nw_mng_if_sel = IXGBE_READ_REG(hw, IXGBE_NW_MNG_IF_SEL);


		phy->ops.setup_internal_link =
					      ixgbe_setup_internal_phy_t_x550em;


		if (hw->mac.type == ixgbe_mac_X550EM_x &&
		    !(IXGBE_READ_REG(hw, IXGBE_FUSES0_GROUP(0)) &
		      IXGBE_FUSES0_REV_MASK))
			phy->ops.enter_lplu = ixgbe_enter_lplu_t_x550em;

		phy->ops.handle_lasi = ixgbe_handle_lasi_ext_t_x550em;
		phy->ops.reset = ixgbe_reset_phy_t_X550em;
		break;
	default:
		break;
	}

	return ret_val;
}
