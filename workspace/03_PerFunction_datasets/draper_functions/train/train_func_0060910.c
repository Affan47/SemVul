mlx4_qp_alloc(struct mlx4_dev *dev, int qpn, struct mlx4_qp *qp, gfp_t gfp)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_qp_table *qp_table = &priv->qp_table;
	int err;

	if (!qpn)
		return -EINVAL;

	qp->qpn = qpn;

	err = mlx4_qp_alloc_icm(dev, qpn, gfp);
	if (err)
		return err;

	spin_lock_irq(&qp_table->lock);
	err = radix_tree_insert(&dev->qp_table_tree, qp->qpn &
				(dev->caps.num_qps - 1), qp);
	spin_unlock_irq(&qp_table->lock);
	if (err)
		goto err_icm;

	atomic_set(&qp->refcount, 1);
	init_completion(&qp->free);

	return 0;

err_icm:
	mlx4_qp_free_icm(dev, qpn);
	return err;
}
