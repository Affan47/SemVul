igb_get_phy_id(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val = 0;
	u16 phy_id;


	if ((hw->mac.type == e1000_i210) || (hw->mac.type == e1000_i211))
		phy->ops.write_reg(hw, I347AT4_PAGE_SELECT, 0);

	ret_val = phy->ops.read_reg(hw, PHY_ID1, &phy_id);
	if (ret_val)
		goto out;

	phy->id = (u32)(phy_id << 16);
	udelay(20);
	ret_val = phy->ops.read_reg(hw, PHY_ID2, &phy_id);
	if (ret_val)
		goto out;

	phy->id |= (u32)(phy_id & PHY_REVISION_MASK);
	phy->revision = (u32)(phy_id & ~PHY_REVISION_MASK);

out:
	return ret_val;
}
