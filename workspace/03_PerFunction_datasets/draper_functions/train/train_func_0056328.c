e1000e_get_phy_id(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val = E1000_SUCCESS;
	u16 phy_id;
	u16 retry_count = 0;

	if (!(phy->ops.read_reg))
		goto out;

	while (retry_count < 2) {
		ret_val = e1e_rphy(hw, PHY_ID1, &phy_id);
		if (ret_val)
			goto out;

		phy->id = (u32)(phy_id << 16);
		udelay(20);
		ret_val = e1e_rphy(hw, PHY_ID2, &phy_id);
		if (ret_val)
			goto out;

		phy->id |= (u32)(phy_id & PHY_REVISION_MASK);
		phy->revision = (u32)(phy_id & ~PHY_REVISION_MASK);

		if (phy->id != 0 && phy->id != PHY_REVISION_MASK)
			goto out;


		ret_val = phy->ops.acquire(hw);
		if (ret_val)
			goto out;
		ret_val = e1000e_set_mdio_slow_mode_hv(hw, true);
		if (ret_val)
			goto out;
		phy->ops.release(hw);

		retry_count++;
	}
out:

	if (retry_count) {
		ret_val = phy->ops.acquire(hw);
		if (ret_val)
			return ret_val;
		ret_val = e1000e_set_mdio_slow_mode_hv(hw, false);
		phy->ops.release(hw);
	}

	return ret_val;
}
