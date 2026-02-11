mlx4_get_eqs_per_port(struct mlx4_dev *dev, u8 port)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	unsigned int i;
	unsigned int sum = 0;

	for (i = 0; i < dev->caps.num_comp_vectors + 1; i++)
		sum += !!test_bit(port - 1,
				  priv->eq_table.eq[i].actv_ports.ports);

	return sum;
}
