bnx2x_calc_ieee_aneg_adv(struct bnx2x_phy *phy,
				     struct link_params *params, u16 *ieee_fc)
{
	struct bnx2x *bp = params->bp;
	*ieee_fc = MDIO_COMBO_IEEE0_AUTO_NEG_ADV_FULL_DUPLEX;


	switch (phy->req_flow_ctrl) {
	case BNX2X_FLOW_CTRL_AUTO:
		switch (params->req_fc_auto_adv) {
		case BNX2X_FLOW_CTRL_BOTH:
		case BNX2X_FLOW_CTRL_RX:
			*ieee_fc |= MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH;
			break;
		case BNX2X_FLOW_CTRL_TX:
			*ieee_fc |=
				MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_ASYMMETRIC;
			break;
		default:
			break;
		}
		break;
	case BNX2X_FLOW_CTRL_TX:
		*ieee_fc |= MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_ASYMMETRIC;
		break;

	case BNX2X_FLOW_CTRL_RX:
	case BNX2X_FLOW_CTRL_BOTH:
		*ieee_fc |= MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH;
		break;

	case BNX2X_FLOW_CTRL_NONE:
	default:
		*ieee_fc |= MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_NONE;
		break;
	}
	DP(NETIF_MSG_LINK, "ieee_fc = 0x%x\n", *ieee_fc);
}
