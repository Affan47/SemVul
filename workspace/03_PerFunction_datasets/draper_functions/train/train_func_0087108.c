niu_init_pcs(struct niu *np)
{
	struct niu_link_config *lp = &np->link_config;
	u64 val;

	switch (np->flags & (NIU_FLAGS_10G |
			     NIU_FLAGS_FIBER |
			     NIU_FLAGS_XCVR_SERDES)) {
	case NIU_FLAGS_FIBER:

		nw64_pcs(PCS_CONF, PCS_CONF_MASK | PCS_CONF_ENABLE);
		nw64_pcs(PCS_DPATH_MODE, 0);
		niu_pcs_mii_reset(np);
		break;

	case NIU_FLAGS_10G:
	case NIU_FLAGS_10G | NIU_FLAGS_FIBER:
	case NIU_FLAGS_10G | NIU_FLAGS_XCVR_SERDES:

		if (!(np->flags & NIU_FLAGS_XMAC))
			return -EINVAL;


		val = nr64_mac(XMAC_CONFIG);
		val &= ~XMAC_CONFIG_10G_XPCS_BYPASS;
		nw64_mac(XMAC_CONFIG, val);

		niu_xpcs_reset(np);

		val = nr64_xpcs(XPCS_CONTROL1);
		if (lp->loopback_mode == LOOPBACK_PHY)
			val |= XPCS_CONTROL1_LOOPBACK;
		else
			val &= ~XPCS_CONTROL1_LOOPBACK;
		nw64_xpcs(XPCS_CONTROL1, val);

		nw64_xpcs(XPCS_DESKEW_ERR_CNT, 0);
		(void) nr64_xpcs(XPCS_SYMERR_CNT01);
		(void) nr64_xpcs(XPCS_SYMERR_CNT23);
		break;


	case NIU_FLAGS_XCVR_SERDES:

		niu_pcs_mii_reset(np);
		nw64_pcs(PCS_CONF, PCS_CONF_MASK | PCS_CONF_ENABLE);
		nw64_pcs(PCS_DPATH_MODE, 0);
		break;

	case 0:

	case NIU_FLAGS_XCVR_SERDES | NIU_FLAGS_FIBER:

		nw64_pcs(PCS_DPATH_MODE, PCS_DPATH_MODE_MII);
		niu_pcs_mii_reset(np);
		break;

	default:
		return -EINVAL;
	}

	return 0;
}
