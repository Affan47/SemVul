e1000_copper_link_autoneg(struct e1000_hw *hw)
{
	s32 ret_val;
	u16 phy_data;


	hw->autoneg_advertised &= AUTONEG_ADVERTISE_SPEED_DEFAULT;


	if (hw->autoneg_advertised == 0)
		hw->autoneg_advertised = AUTONEG_ADVERTISE_SPEED_DEFAULT;


	if (hw->phy_type == e1000_phy_8201)
		hw->autoneg_advertised &= AUTONEG_ADVERTISE_10_100_ALL;

	e_dbg("Reconfiguring auto-neg advertisement params\n");
	ret_val = e1000_phy_setup_autoneg(hw);
	if (ret_val) {
		e_dbg("Error Setting up Auto-Negotiation\n");
		return ret_val;
	}
	e_dbg("Restarting Auto-Neg\n");


	ret_val = e1000_read_phy_reg(hw, PHY_CTRL, &phy_data);
	if (ret_val)
		return ret_val;

	phy_data |= (MII_CR_AUTO_NEG_EN | MII_CR_RESTART_AUTO_NEG);
	ret_val = e1000_write_phy_reg(hw, PHY_CTRL, phy_data);
	if (ret_val)
		return ret_val;


	if (hw->wait_autoneg_complete) {
		ret_val = e1000_wait_autoneg(hw);
		if (ret_val) {
			e_dbg
			    ("Error while waiting for autoneg to complete\n");
			return ret_val;
		}
	}

	hw->get_link_status = true;

	return E1000_SUCCESS;
}
