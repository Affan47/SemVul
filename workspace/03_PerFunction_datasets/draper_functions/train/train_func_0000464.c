stmmac_suspend(struct net_device *ndev)
{
	struct stmmac_priv *priv = netdev_priv(ndev);
	unsigned long flags;

	if (!ndev || !netif_running(ndev))
		return 0;

	if (priv->phydev)
		phy_stop(priv->phydev);

	spin_lock_irqsave(&priv->lock, flags);

	netif_device_detach(ndev);
	netif_stop_queue(ndev);

	napi_disable(&priv->napi);


	priv->hw->dma->stop_tx(priv->ioaddr);
	priv->hw->dma->stop_rx(priv->ioaddr);


	if (device_may_wakeup(priv->device)) {
		priv->hw->mac->pmt(priv->hw, priv->wolopts);
		priv->irq_wake = 1;
	} else {
		stmmac_set_mac(priv->ioaddr, false);
		pinctrl_pm_select_sleep_state(priv->device);

		clk_disable(priv->pclk);
		clk_disable(priv->stmmac_clk);
	}
	spin_unlock_irqrestore(&priv->lock, flags);

	priv->oldlink = 0;
	priv->speed = 0;
	priv->oldduplex = -1;
	return 0;
}
