sky2_phy_power_up(struct sky2_hw *hw, unsigned port)
{
	u32 reg1;

	sky2_write8(hw, B2_TST_CTRL1, TST_CFG_WRITE_ON);
	reg1 = sky2_pci_read32(hw, PCI_DEV_REG1);
	reg1 &= ~phy_power[port];

	if (hw->chip_id == CHIP_ID_YUKON_XL && hw->chip_rev > CHIP_REV_YU_XL_A1)
		reg1 |= coma_mode[port];

	sky2_pci_write32(hw, PCI_DEV_REG1, reg1);
	sky2_write8(hw, B2_TST_CTRL1, TST_CFG_WRITE_OFF);
	sky2_pci_read32(hw, PCI_DEV_REG1);

	if (hw->chip_id == CHIP_ID_YUKON_FE)
		gm_phy_write(hw, port, PHY_MARV_CTRL, PHY_CT_ANE);
	else if (hw->flags & SKY2_HW_ADV_POWER_CTL)
		sky2_write8(hw, SK_REG(port, GPHY_CTRL), GPC_RST_CLR);
}
