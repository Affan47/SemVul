mlx4_reset_vf_support(struct mlx4_dev *dev)
{
#define COMM_CHAN_RST_OFFSET 0x1e

	struct mlx4_priv *priv = mlx4_priv(dev);
	u32 comm_rst;
	u32 comm_caps;

	comm_caps = swab32(readl((__iomem char *)priv->mfunc.comm +
				 MLX4_COMM_CHAN_CAPS));
	comm_rst = (comm_caps & (u32)(1 << COMM_CHAN_RST_OFFSET));

	if (comm_rst)
		dev->caps.vf_caps |= MLX4_VF_CAP_FLAG_RESET;
}
