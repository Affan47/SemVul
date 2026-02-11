bcmgenet_close(struct net_device *dev)
{
	struct bcmgenet_priv *priv = netdev_priv(dev);
	int ret;

	netif_dbg(priv, ifdown, dev, "bcmgenet_close\n");

	bcmgenet_netif_stop(dev);


	phy_disconnect(priv->phydev);


	umac_enable_set(priv, CMD_RX_EN, false);

	ret = bcmgenet_dma_teardown(priv);
	if (ret)
		return ret;


	umac_enable_set(priv, CMD_TX_EN, false);


	bcmgenet_tx_reclaim_all(dev);
	bcmgenet_fini_dma(priv);

	free_irq(priv->irq0, priv);
	free_irq(priv->irq1, priv);

	if (priv->internal_phy)
		ret = bcmgenet_power_down(priv, GENET_POWER_PASSIVE);

	clk_disable_unprepare(priv->clk);

	return ret;
}
