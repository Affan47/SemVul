xgbe_suspend(struct device *dev)
{
	struct net_device *netdev = dev_get_drvdata(dev);
	struct xgbe_prv_data *pdata = netdev_priv(netdev);
	int ret = 0;

	DBGPR("-->xgbe_suspend\n");

	if (netif_running(netdev))
		ret = xgbe_powerdown(netdev, XGMAC_DRIVER_CONTEXT);

	pdata->lpm_ctrl = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_CTRL1);
	pdata->lpm_ctrl |= MDIO_CTRL1_LPOWER;
	XMDIO_WRITE(pdata, MDIO_MMD_PCS, MDIO_CTRL1, pdata->lpm_ctrl);

	DBGPR("<--xgbe_suspend\n");

	return ret;
}
