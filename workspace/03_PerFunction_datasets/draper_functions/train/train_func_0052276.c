e1000_k1_gig_workaround_hv(struct e1000_hw *hw, bool link)
{
	s32 ret_val = 0;
	u16 status_reg = 0;
	bool k1_enable = hw->dev_spec.ich8lan.nvm_k1_enabled;

	if (hw->mac.type != e1000_pchlan)
		return 0;


	ret_val = hw->phy.ops.acquire(hw);
	if (ret_val)
		return ret_val;


	if (link) {
		if (hw->phy.type == e1000_phy_82578) {
			ret_val = e1e_rphy_locked(hw, BM_CS_STATUS,
						  &status_reg);
			if (ret_val)
				goto release;

			status_reg &= (BM_CS_STATUS_LINK_UP |
				       BM_CS_STATUS_RESOLVED |
				       BM_CS_STATUS_SPEED_MASK);

			if (status_reg == (BM_CS_STATUS_LINK_UP |
					   BM_CS_STATUS_RESOLVED |
					   BM_CS_STATUS_SPEED_1000))
				k1_enable = false;
		}

		if (hw->phy.type == e1000_phy_82577) {
			ret_val = e1e_rphy_locked(hw, HV_M_STATUS, &status_reg);
			if (ret_val)
				goto release;

			status_reg &= (HV_M_STATUS_LINK_UP |
				       HV_M_STATUS_AUTONEG_COMPLETE |
				       HV_M_STATUS_SPEED_MASK);

			if (status_reg == (HV_M_STATUS_LINK_UP |
					   HV_M_STATUS_AUTONEG_COMPLETE |
					   HV_M_STATUS_SPEED_1000))
				k1_enable = false;
		}


		ret_val = e1e_wphy_locked(hw, PHY_REG(770, 19), 0x0100);
		if (ret_val)
			goto release;

	} else {

		ret_val = e1e_wphy_locked(hw, PHY_REG(770, 19), 0x4100);
		if (ret_val)
			goto release;
	}

	ret_val = e1000_configure_k1_ich8lan(hw, k1_enable);

release:
	hw->phy.ops.release(hw);

	return ret_val;
}
