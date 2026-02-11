e1000_set_d3_lplu_state_82541(struct e1000_hw *hw, bool active)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data;

	DEBUGFUNC("e1000_set_d3_lplu_state_82541");

	switch (hw->mac.type) {
	case e1000_82541_rev_2:
	case e1000_82547_rev_2:
		break;
	default:
		ret_val = e1000_set_d3_lplu_state_generic(hw, active);
		goto out;
		break;
	}

	ret_val = phy->ops.read_reg(hw, IGP01E1000_GMII_FIFO, &data);
	if (ret_val)
		goto out;

	if (!active) {
		data &= ~IGP01E1000_GMII_FLEX_SPD;
		ret_val = phy->ops.write_reg(hw, IGP01E1000_GMII_FIFO, data);
		if (ret_val)
			goto out;


		if (phy->smart_speed == e1000_smart_speed_on) {
			ret_val = phy->ops.read_reg(hw,
			                            IGP01E1000_PHY_PORT_CONFIG,
			                            &data);
			if (ret_val)
				goto out;

			data |= IGP01E1000_PSCFR_SMART_SPEED;
			ret_val = phy->ops.write_reg(hw,
			                             IGP01E1000_PHY_PORT_CONFIG,
			                             data);
			if (ret_val)
				goto out;
		} else if (phy->smart_speed == e1000_smart_speed_off) {
			ret_val = phy->ops.read_reg(hw,
			                            IGP01E1000_PHY_PORT_CONFIG,
			                            &data);
			if (ret_val)
				goto out;

			data &= ~IGP01E1000_PSCFR_SMART_SPEED;
			ret_val = phy->ops.write_reg(hw,
			                             IGP01E1000_PHY_PORT_CONFIG,
			                             data);
			if (ret_val)
				goto out;
		}
	} else if ((phy->autoneg_advertised == E1000_ALL_SPEED_DUPLEX) ||
	           (phy->autoneg_advertised == E1000_ALL_NOT_GIG) ||
	           (phy->autoneg_advertised == E1000_ALL_10_SPEED)) {
		data |= IGP01E1000_GMII_FLEX_SPD;
		ret_val = phy->ops.write_reg(hw, IGP01E1000_GMII_FIFO, data);
		if (ret_val)
			goto out;


		ret_val = phy->ops.read_reg(hw,
		                            IGP01E1000_PHY_PORT_CONFIG,
		                            &data);
		if (ret_val)
			goto out;

		data &= ~IGP01E1000_PSCFR_SMART_SPEED;
		ret_val = phy->ops.write_reg(hw,
		                             IGP01E1000_PHY_PORT_CONFIG,
		                             data);
	}

out:
	return ret_val;
}
