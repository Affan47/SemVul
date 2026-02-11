mlx4_is_eq_shared(struct mlx4_dev *dev, int vector)
{
	struct mlx4_priv *priv = mlx4_priv(dev);

	vector = MLX4_CQ_TO_EQ_VECTOR(vector);
	if (vector <= 0 || (vector >= dev->caps.num_comp_vectors + 1))
		return -EINVAL;

	return !!(bitmap_weight(priv->eq_table.eq[vector].actv_ports.ports,
				dev->caps.num_ports) > 1);
}
