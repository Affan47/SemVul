mlx5_cqwq_create(struct mlx5_core_dev *mdev, struct mlx5_wq_param *param,
		     void *cqc, struct mlx5_cqwq *wq,
		     struct mlx5_wq_ctrl *wq_ctrl)
{
	int err;

	wq->log_stride = 6 + MLX5_GET(cqc, cqc, cqe_sz);
	wq->log_sz = MLX5_GET(cqc, cqc, log_cq_size);
	wq->sz_m1 = (1 << wq->log_sz) - 1;

	err = mlx5_db_alloc_node(mdev, &wq_ctrl->db, param->db_numa_node);
	if (err) {
		mlx5_core_warn(mdev, "mlx5_db_alloc() failed, %d\n", err);
		return err;
	}

	err = mlx5_buf_alloc_node(mdev, mlx5_cqwq_get_byte_size(wq),
				  &wq_ctrl->buf, param->buf_numa_node);
	if (err) {
		mlx5_core_warn(mdev, "mlx5_buf_alloc() failed, %d\n", err);
		goto err_db_free;
	}

	wq->buf = wq_ctrl->buf.direct.buf;
	wq->db  = wq_ctrl->db.db;

	wq_ctrl->mdev = mdev;

	return 0;

err_db_free:
	mlx5_db_free(mdev, &wq_ctrl->db);

	return err;
}
