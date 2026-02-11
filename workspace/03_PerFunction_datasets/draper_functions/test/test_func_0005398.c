bnx2x_dcbnl_set_pfc_cfg(struct net_device *netdev, int prio,
				    u8 setting)
{
	struct bnx2x *bp = netdev_priv(netdev);
	DP(BNX2X_MSG_DCB, "prio[%d] = %d\n", prio, setting);

	if (!bnx2x_dcbnl_set_valid(bp) || prio >= MAX_PFC_PRIORITIES)
		return;

	if (setting) {
		bp->dcbx_config_params.admin_pfc_bitmap |= (1 << prio);
		bp->dcbx_config_params.admin_pfc_tx_enable = 1;
	} else {
		bp->dcbx_config_params.admin_pfc_bitmap &= ~(1 << prio);
	}
}
