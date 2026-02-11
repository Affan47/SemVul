bnx2x_8726_read_status(struct bnx2x_phy *phy,
				 struct link_params *params,
				 struct link_vars *vars)
{
	struct bnx2x *bp = params->bp;
	u16 val1;
	u8 link_up = bnx2x_8706_8726_read_status(phy, params, vars);
	if (link_up) {
		bnx2x_cl45_read(bp, phy,
				MDIO_PMA_DEVAD, MDIO_PMA_REG_PHY_IDENTIFIER,
				&val1);
		if (val1 & (1<<15)) {
			DP(NETIF_MSG_LINK, "Tx is disabled\n");
			link_up = 0;
			vars->line_speed = 0;
		}
	}
	return link_up;
}
