mlx4_get_slave_node_guid(struct mlx4_dev *dev, int slave)
{
	struct mlx4_priv *priv = container_of(dev, struct mlx4_priv, dev);

	if (!mlx4_is_master(dev))
		return 0;

	return priv->slave_node_guids[slave];
}
