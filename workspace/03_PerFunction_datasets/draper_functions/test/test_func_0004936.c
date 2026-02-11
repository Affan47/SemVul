mlx4_slave_event(struct mlx4_dev *dev, int slave,
			     struct mlx4_eqe *eqe)
{
	struct mlx4_priv *priv = mlx4_priv(dev);

	if (slave < 0 || slave > dev->persist->num_vfs ||
	    slave == dev->caps.function ||
	    !priv->mfunc.master.slave_state[slave].active)
		return;

	slave_event(dev, slave, eqe);
}
