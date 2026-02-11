bnx2x_dcbnl_set_featcfg(struct net_device *netdev, int featid,
				  u8 flags)
{
	struct bnx2x *bp = netdev_priv(netdev);
	u8 rval = 0;

	DP(BNX2X_MSG_DCB, "featid = %d flags = %02x\n", featid, flags);


	if (bnx2x_dcbnl_set_valid(bp)) {
		switch (featid) {
		case DCB_FEATCFG_ATTR_PG:
			bp->dcbx_config_params.admin_ets_enable =
				flags & DCB_FEATCFG_ENABLE ? 1 : 0;
			bp->dcbx_config_params.admin_ets_willing =
				flags & DCB_FEATCFG_WILLING ? 1 : 0;
			break;
		case DCB_FEATCFG_ATTR_PFC:
			bp->dcbx_config_params.admin_pfc_enable =
				flags & DCB_FEATCFG_ENABLE ? 1 : 0;
			bp->dcbx_config_params.admin_pfc_willing =
				flags & DCB_FEATCFG_WILLING ? 1 : 0;
			break;
		case DCB_FEATCFG_ATTR_APP:

			bp->dcbx_config_params.admin_app_priority_willing =
				flags & DCB_FEATCFG_WILLING ? 1 : 0;
			break;
		default:
			BNX2X_ERR("Non valid feature-ID\n");
			rval = 1;
			break;
		}
	} else {
		DP(BNX2X_MSG_DCB, "dcbnl call not valid\n");
		rval = 1;
	}

	return rval;
}
