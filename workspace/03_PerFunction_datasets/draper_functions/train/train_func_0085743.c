e1000_init_phy_params_82541(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val = E1000_SUCCESS;

	DEBUGFUNC("e1000_init_phy_params_82541");

	phy->addr                      = 1;
	phy->autoneg_mask              = AUTONEG_ADVERTISE_SPEED_DEFAULT;
	phy->reset_delay_us            = 10000;
	phy->type                      = e1000_phy_igp;


	phy->ops.check_polarity        = e1000_check_polarity_igp;
#if 0
	phy->ops.force_speed_duplex    = e1000_phy_force_speed_duplex_igp;
#endif
#if 0
	phy->ops.get_cable_length      = e1000_get_cable_length_igp_82541;
#endif
	phy->ops.get_cfg_done          = e1000_get_cfg_done_generic;
	phy->ops.get_info              = e1000_get_phy_info_igp;
	phy->ops.read_reg              = e1000_read_phy_reg_igp;
	phy->ops.reset                 = e1000_phy_hw_reset_82541;
	phy->ops.set_d3_lplu_state     = e1000_set_d3_lplu_state_82541;
	phy->ops.write_reg             = e1000_write_phy_reg_igp;
	phy->ops.power_up              = e1000_power_up_phy_copper;
	phy->ops.power_down            = e1000_power_down_phy_copper_82541;

	ret_val = e1000_get_phy_id(hw);
	if (ret_val)
		goto out;


	if (phy->id != IGP01E1000_I_PHY_ID) {
		ret_val = -E1000_ERR_PHY;
		goto out;
	}

out:
	return ret_val;
}
