mlx4_free_resource_tracker(struct mlx4_dev *dev,
				enum mlx4_res_tracker_free_type type)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	int i;

	if (priv->mfunc.master.res_tracker.slave_list) {
		if (type != RES_TR_FREE_STRUCTS_ONLY) {
			for (i = 0; i < dev->num_slaves; i++) {
				if (type == RES_TR_FREE_ALL ||
				    dev->caps.function != i)
					mlx4_delete_all_resources_for_slave(dev, i);
			}

			i = dev->caps.function;
			mlx4_reset_roce_gids(dev, i);
			mutex_lock(&priv->mfunc.master.res_tracker.slave_list[i].mutex);
			rem_slave_vlans(dev, i);
			mutex_unlock(&priv->mfunc.master.res_tracker.slave_list[i].mutex);
		}

		if (type != RES_TR_FREE_SLAVES_ONLY) {
			for (i = 0; i < MLX4_NUM_OF_RESOURCE_TYPE; i++) {
				kfree(priv->mfunc.master.res_tracker.res_alloc[i].allocated);
				priv->mfunc.master.res_tracker.res_alloc[i].allocated = NULL;
				kfree(priv->mfunc.master.res_tracker.res_alloc[i].guaranteed);
				priv->mfunc.master.res_tracker.res_alloc[i].guaranteed = NULL;
				kfree(priv->mfunc.master.res_tracker.res_alloc[i].quota);
				priv->mfunc.master.res_tracker.res_alloc[i].quota = NULL;
			}
			kfree(priv->mfunc.master.res_tracker.slave_list);
			priv->mfunc.master.res_tracker.slave_list = NULL;
		}
	}
}
