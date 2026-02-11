mlx5e_open_sqs(struct mlx5e_channel *c,
			  struct mlx5e_channel_param *cparam)
{
	int err;
	int tc;

	for (tc = 0; tc < c->num_tc; tc++) {
		err = mlx5e_open_sq(c, tc, &cparam->sq, &c->sq[tc]);
		if (err)
			goto err_close_sqs;
	}

	return 0;

err_close_sqs:
	for (tc--; tc >= 0; tc--)
		mlx5e_close_sq(&c->sq[tc]);

	return err;
}
