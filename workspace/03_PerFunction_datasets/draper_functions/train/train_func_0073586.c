stmmac_get_sset_count(struct net_device *netdev, int sset)
{
	struct stmmac_priv *priv = netdev_priv(netdev);
	int len;

	switch (sset) {
	case ETH_SS_STATS:
		len = STMMAC_STATS_LEN;

		if (priv->dma_cap.rmon)
			len += STMMAC_MMC_STATS_LEN;

		return len;
	default:
		return -EOPNOTSUPP;
	}
}
