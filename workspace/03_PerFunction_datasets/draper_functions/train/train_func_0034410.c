num_med_uuar(struct mlx5_uuar_info *uuari)
{
	int n;

	n = uuari->num_uars * MLX5_NON_FP_BF_REGS_PER_PAGE -
		uuari->num_low_latency_uuars - 1;

	return n >= 0 ? n : 0;
}
