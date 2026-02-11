e1000_read_phy_reg_ex(struct e1000_hw *hw, u32 reg_addr,
				 u16 *phy_data)
{
	u32 i;
	u32 mdic = 0;
	const u32 phy_addr = (hw->mac_type == e1000_ce4100) ? hw->phy_addr : 1;

	if (reg_addr > MAX_PHY_REG_ADDRESS) {
		e_dbg("PHY Address %d is out of range\n", reg_addr);
		return -E1000_ERR_PARAM;
	}

	if (hw->mac_type > e1000_82543) {


		if (hw->mac_type == e1000_ce4100) {
			mdic = ((reg_addr << E1000_MDIC_REG_SHIFT) |
				(phy_addr << E1000_MDIC_PHY_SHIFT) |
				(INTEL_CE_GBE_MDIC_OP_READ) |
				(INTEL_CE_GBE_MDIC_GO));

			writel(mdic, E1000_MDIO_CMD);


			for (i = 0; i < 64; i++) {
				udelay(50);
				mdic = readl(E1000_MDIO_CMD);
				if (!(mdic & INTEL_CE_GBE_MDIC_GO))
					break;
			}

			if (mdic & INTEL_CE_GBE_MDIC_GO) {
				e_dbg("MDI Read did not complete\n");
				return -E1000_ERR_PHY;
			}

			mdic = readl(E1000_MDIO_STS);
			if (mdic & INTEL_CE_GBE_MDIC_READ_ERROR) {
				e_dbg("MDI Read Error\n");
				return -E1000_ERR_PHY;
			}
			*phy_data = (u16)mdic;
		} else {
			mdic = ((reg_addr << E1000_MDIC_REG_SHIFT) |
				(phy_addr << E1000_MDIC_PHY_SHIFT) |
				(E1000_MDIC_OP_READ));

			ew32(MDIC, mdic);


			for (i = 0; i < 64; i++) {
				udelay(50);
				mdic = er32(MDIC);
				if (mdic & E1000_MDIC_READY)
					break;
			}
			if (!(mdic & E1000_MDIC_READY)) {
				e_dbg("MDI Read did not complete\n");
				return -E1000_ERR_PHY;
			}
			if (mdic & E1000_MDIC_ERROR) {
				e_dbg("MDI Error\n");
				return -E1000_ERR_PHY;
			}
			*phy_data = (u16)mdic;
		}
	} else {


		e1000_shift_out_mdi_bits(hw, PHY_PREAMBLE, PHY_PREAMBLE_SIZE);


		mdic = ((reg_addr) | (phy_addr << 5) |
			(PHY_OP_READ << 10) | (PHY_SOF << 12));

		e1000_shift_out_mdi_bits(hw, mdic, 14);


		*phy_data = e1000_shift_in_mdi_bits(hw);
	}
	return E1000_SUCCESS;
}
