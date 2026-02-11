mlx4_ib_gid_index_to_real_index(struct mlx4_ib_dev *ibdev,
				    u8 port_num, int index)
{
	struct mlx4_ib_iboe *iboe = &ibdev->iboe;
	struct gid_cache_context *ctx = NULL;
	union ib_gid gid;
	struct mlx4_port_gid_table   *port_gid_table;
	int real_index = -EINVAL;
	int i;
	int ret;
	unsigned long flags;

	if (port_num > MLX4_MAX_PORTS)
		return -EINVAL;

	if (mlx4_is_bonded(ibdev->dev))
		port_num = 1;

	if (!rdma_cap_roce_gid_table(&ibdev->ib_dev, port_num))
		return index;

	ret = ib_get_cached_gid(&ibdev->ib_dev, port_num, index, &gid, NULL);
	if (ret)
		return ret;

	if (!memcmp(&gid, &zgid, sizeof(gid)))
		return -EINVAL;

	spin_lock_irqsave(&iboe->lock, flags);
	port_gid_table = &iboe->gids[port_num - 1];

	for (i = 0; i < MLX4_MAX_PORT_GIDS; ++i)
		if (!memcmp(&port_gid_table->gids[i].gid, &gid, sizeof(gid))) {
			ctx = port_gid_table->gids[i].ctx;
			break;
		}
	if (ctx)
		real_index = ctx->real_index;
	spin_unlock_irqrestore(&iboe->lock, flags);
	return real_index;
}
