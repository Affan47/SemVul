bnx2x_peer_appinfo(struct net_device *netdev,
			      struct dcb_peer_app_info *info, u16* app_count)
{
	int i;
	struct bnx2x *bp = netdev_priv(netdev);

	DP(BNX2X_MSG_DCB, "APP-INFO\n");

	info->willing = (bp->dcbx_remote_flags & DCBX_APP_REM_WILLING) ?: 0;
	info->error = (bp->dcbx_remote_flags & DCBX_APP_RX_ERROR) ?: 0;
	*app_count = 0;

	for (i = 0; i < DCBX_MAX_APP_PROTOCOL; i++)
		if (bp->dcbx_remote_feat.app.app_pri_tbl[i].appBitfield &
		    DCBX_APP_ENTRY_VALID)
			(*app_count)++;
	return 0;
}
