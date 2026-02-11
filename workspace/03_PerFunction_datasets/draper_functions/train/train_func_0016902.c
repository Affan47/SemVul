atl1c_start_phy_polling(struct atl1c_hw *hw, u16 clk_sel)
{
	u32 val;

	if (!(hw->ctrl_flags & ATL1C_FPGA_VERSION))
		return;

	val = MDIO_CTRL_SPRES_PRMBL |
		FIELDX(MDIO_CTRL_CLK_SEL, clk_sel) |
		FIELDX(MDIO_CTRL_REG, 1) |
		MDIO_CTRL_START |
		MDIO_CTRL_OP_READ;
	AT_WRITE_REG(hw, REG_MDIO_CTRL, val);
	atl1c_wait_mdio_idle(hw);
	val |= MDIO_CTRL_AP_EN;
	val &= ~MDIO_CTRL_START;
	AT_WRITE_REG(hw, REG_MDIO_CTRL, val);
	udelay(30);
}
