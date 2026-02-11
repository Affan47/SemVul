m_can_suspend(struct device *dev)
{
	struct net_device *ndev = dev_get_drvdata(dev);
	struct m_can_priv *priv = netdev_priv(ndev);

	if (netif_running(ndev)) {
		netif_stop_queue(ndev);
		netif_device_detach(ndev);
	}


	priv->can.state = CAN_STATE_SLEEPING;

	return 0;
}
