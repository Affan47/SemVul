ql_display_dev_info(struct net_device *ndev)
{
	struct ql_adapter *qdev = netdev_priv(ndev);

	netif_info(qdev, probe, qdev->ndev,
		   "Function #%d, Port %d, NIC Roll %d, NIC Rev = %d, "
		   "XG Roll = %d, XG Rev = %d.\n",
		   qdev->func,
		   qdev->port,
		   qdev->chip_rev_id & 0x0000000f,
		   qdev->chip_rev_id >> 4 & 0x0000000f,
		   qdev->chip_rev_id >> 8 & 0x0000000f,
		   qdev->chip_rev_id >> 12 & 0x0000000f);
	netif_info(qdev, probe, qdev->ndev,
		   "MAC address %pM\n", ndev->dev_addr);
}
