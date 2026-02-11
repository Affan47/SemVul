mlx5e_napi_poll(struct napi_struct *napi, int budget)
{
	struct mlx5e_channel *c = container_of(napi, struct mlx5e_channel,
					       napi);
	bool busy = false;
	int i;

	clear_bit(MLX5E_CHANNEL_NAPI_SCHED, &c->flags);

	for (i = 0; i < c->num_tc; i++)
		busy |= mlx5e_poll_tx_cq(&c->sq[i].cq);

	busy |= mlx5e_poll_rx_cq(&c->rq.cq, budget);

	busy |= mlx5e_post_rx_wqes(&c->rq);

	if (busy)
		return budget;

	napi_complete(napi);


	if (test_bit(MLX5E_CHANNEL_NAPI_SCHED, &c->flags)) {
		napi_schedule(napi);
		return 0;
	}

	for (i = 0; i < c->num_tc; i++)
		mlx5e_cq_arm(&c->sq[i].cq);
	mlx5e_cq_arm(&c->rq.cq);

	return 0;
}
