handle_unexisting_counter(struct mlx4_dev *dev,
				     struct mlx4_qp_context *qpc, u8 slave,
				     int port)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	struct res_common *tmp;
	struct res_counter *counter;
	u64 counter_idx = MLX4_SINK_COUNTER_INDEX(dev);
	int err = 0;

	spin_lock_irq(mlx4_tlock(dev));
	list_for_each_entry(tmp,
			    &tracker->slave_list[slave].res_list[RES_COUNTER],
			    list) {
		counter = container_of(tmp, struct res_counter, com);
		if (port == counter->port) {
			qpc->pri_path.counter_index  = counter->com.res_id;
			spin_unlock_irq(mlx4_tlock(dev));
			return 0;
		}
	}
	spin_unlock_irq(mlx4_tlock(dev));


	err = counter_alloc_res(dev, slave, RES_OP_RESERVE, 0, 0, &counter_idx,
				port);
	if (err == -ENOENT) {
		err = 0;
	} else if (err && err != -ENOSPC) {
		mlx4_err(dev, "%s: failed to create new counter for slave %d err %d\n",
			 __func__, slave, err);
	} else {
		qpc->pri_path.counter_index = counter_idx;
		mlx4_dbg(dev, "%s: alloc new counter for slave %d index %d\n",
			 __func__, slave, qpc->pri_path.counter_index);
		err = 0;
	}

	return err;
}
