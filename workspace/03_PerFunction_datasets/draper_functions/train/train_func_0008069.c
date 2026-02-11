mlx4_comm_check_offline(struct mlx4_dev *dev)
{
#define COMM_CHAN_OFFLINE_OFFSET 0x09

	u32 comm_flags;
	u32 offline_bit;
	unsigned long end;
	struct mlx4_priv *priv = mlx4_priv(dev);

	end = msecs_to_jiffies(MLX4_COMM_OFFLINE_TIME_OUT) + jiffies;
	while (time_before(jiffies, end)) {
		comm_flags = swab32(readl((__iomem char *)priv->mfunc.comm +
					  MLX4_COMM_CHAN_FLAGS));
		offline_bit = (comm_flags &
			       (u32)(1 << COMM_CHAN_OFFLINE_OFFSET));
		if (!offline_bit)
			return 0;


		if (dev->persist->interface_state &
		    MLX4_INTERFACE_STATE_NOWAIT)
			break;


		msleep(100);
	}
	mlx4_err(dev, "Communication channel is offline.\n");
	return -EIO;
}
