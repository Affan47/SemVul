igb_read_phy_reg_mdic(struct e1000_hw *hw, u32 offset, u16 *data)
{
	struct e1000_phy_info *phy = &hw->phy;
	u32 i, mdic = 0;
	s32 ret_val = 0;

	if (offset > MAX_PHY_REG_ADDRESS) {
		hw_dbg("PHY Address %d is out of range\n", offset);
		ret_val = -E1000_ERR_PARAM;
		goto out;
	}


	mdic = ((offset << E1000_MDIC_REG_SHIFT) |
		(phy->addr << E1000_MDIC_PHY_SHIFT) |
		(E1000_MDIC_OP_READ));

	wr32(E1000_MDIC, mdic);


	for (i = 0; i < (E1000_GEN_POLL_TIMEOUT * 3); i++) {
		udelay(50);
		mdic = rd32(E1000_MDIC);
		if (mdic & E1000_MDIC_READY)
			break;
	}
	if (!(mdic & E1000_MDIC_READY)) {
		hw_dbg("MDI Read did not complete\n");
		ret_val = -E1000_ERR_PHY;
		goto out;
	}
	if (mdic & E1000_MDIC_ERROR) {
		hw_dbg("MDI Error\n");
		ret_val = -E1000_ERR_PHY;
		goto out;
	}
	*data = (u16) mdic;

out:
	return ret_val;
}
