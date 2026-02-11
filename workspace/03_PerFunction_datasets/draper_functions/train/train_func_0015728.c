mlx5e_get_coalesce(struct net_device *netdev,
			      struct ethtool_coalesce *coal)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);

	if (!MLX5_CAP_GEN(priv->mdev, cq_moderation))
		return -ENOTSUPP;

	coal->rx_coalesce_usecs       = priv->params.rx_cq_moderation_usec;
	coal->rx_max_coalesced_frames = priv->params.rx_cq_moderation_pkts;
	coal->tx_coalesce_usecs       = priv->params.tx_cq_moderation_usec;
	coal->tx_max_coalesced_frames = priv->params.tx_cq_moderation_pkts;

	return 0;
}
