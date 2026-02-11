bnx2x_dcbnl_set_pfc_state(struct net_device *netdev, u8 state)
{
	struct bnx2x *bp = netdev_priv(netdev);
	DP(BNX2X_MSG_DCB, "state = %s\n", state ? "on" : "off");

	if (!bnx2x_dcbnl_set_valid(bp))
		return;

	bp->dcbx_config_params.admin_pfc_tx_enable =
	bp->dcbx_config_params.admin_pfc_enable = (state ? 1 : 0);
}
