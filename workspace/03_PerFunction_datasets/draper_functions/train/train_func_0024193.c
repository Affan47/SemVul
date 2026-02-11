ql_get_settings(struct net_device *ndev, struct ethtool_cmd *ecmd)
{
	struct ql3_adapter *qdev = netdev_priv(ndev);

	ecmd->transceiver = XCVR_INTERNAL;
	ecmd->supported = ql_supported_modes(qdev);

	if (test_bit(QL_LINK_OPTICAL, &qdev->flags)) {
		ecmd->port = PORT_FIBRE;
	} else {
		ecmd->port = PORT_TP;
		ecmd->phy_address = qdev->PHYAddr;
	}
	ecmd->advertising = ql_supported_modes(qdev);
	ecmd->autoneg = ql_get_auto_cfg_status(qdev);
	ethtool_cmd_speed_set(ecmd, ql_get_speed(qdev));
	ecmd->duplex = ql_get_full_dup(qdev);
	return 0;
}
