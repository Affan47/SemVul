mlx5e_create_sq(struct mlx5e_channel *c,
			   int tc,
			   struct mlx5e_sq_param *param,
			   struct mlx5e_sq *sq)
{
	struct mlx5e_priv *priv = c->priv;
	struct mlx5_core_dev *mdev = priv->mdev;

	void *sqc = param->sqc;
	void *sqc_wq = MLX5_ADDR_OF(sqc, sqc, wq);
	int txq_ix;
	int err;

	err = mlx5_alloc_map_uar(mdev, &sq->uar);
	if (err)
		return err;

	param->wq.db_numa_node = cpu_to_node(c->cpu);

	err = mlx5_wq_cyc_create(mdev, &param->wq, sqc_wq, &sq->wq,
				 &sq->wq_ctrl);
	if (err)
		goto err_unmap_free_uar;

	sq->wq.db       = &sq->wq.db[MLX5_SND_DBR];
	sq->uar_map     = sq->uar.map;
	sq->uar_bf_map  = sq->uar.bf_map;
	sq->bf_buf_size = (1 << MLX5_CAP_GEN(mdev, log_bf_reg_size)) / 2;
	sq->max_inline  = param->max_inline;

	err = mlx5e_alloc_sq_db(sq, cpu_to_node(c->cpu));
	if (err)
		goto err_sq_wq_destroy;

	txq_ix = c->ix + tc * priv->params.num_channels;
	sq->txq = netdev_get_tx_queue(priv->netdev, txq_ix);

	sq->pdev      = c->pdev;
	sq->mkey_be   = c->mkey_be;
	sq->channel   = c;
	sq->tc        = tc;
	sq->edge      = (sq->wq.sz_m1 + 1) - MLX5_SEND_WQE_MAX_WQEBBS;
	sq->bf_budget = MLX5E_SQ_BF_BUDGET;
	priv->txq_to_sq_map[txq_ix] = sq;

	return 0;

err_sq_wq_destroy:
	mlx5_wq_destroy(&sq->wq_ctrl);

err_unmap_free_uar:
	mlx5_unmap_free_uar(mdev, &sq->uar);

	return err;
}
