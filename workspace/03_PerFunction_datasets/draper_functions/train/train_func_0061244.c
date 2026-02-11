mlx5e_fill_rqt_rqns(struct mlx5e_priv *priv, void *rqtc,
				enum mlx5e_rqt_ix rqt_ix)
{

	switch (rqt_ix) {
	case MLX5E_INDIRECTION_RQT:
		mlx5e_fill_indir_rqt_rqns(priv, rqtc);

		break;

	default:
		MLX5_SET(rqtc, rqtc, rq_num[0],
			 test_bit(MLX5E_STATE_OPENED, &priv->state) ?
			 priv->channel[0]->rq.rqn :
			 priv->drop_rq.rqn);

		break;
	}
}
