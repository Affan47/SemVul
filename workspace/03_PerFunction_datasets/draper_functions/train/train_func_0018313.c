bnx2x_warpcore_set_lpi_passthrough(struct bnx2x_phy *phy,
					       struct link_params *params)
{
	struct bnx2x *bp = params->bp;

	DP(NETIF_MSG_LINK, "Configure WC for LPI pass through\n");
	bnx2x_cl45_write(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_EEE_COMBO_CONTROL0, 0x7c);
	bnx2x_cl45_read_or_write(bp, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_DIGITAL4_MISC5, 0xc000);
}
