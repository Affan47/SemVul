mlx5_set_port_admin_status(struct mlx5_core_dev *dev,
			       enum mlx5_port_status status)
{
	u32 in[MLX5_ST_SZ_DW(paos_reg)];
	u32 out[MLX5_ST_SZ_DW(paos_reg)];

	memset(in, 0, sizeof(in));

	MLX5_SET(paos_reg, in, local_port, 1);
	MLX5_SET(paos_reg, in, admin_status, status);
	MLX5_SET(paos_reg, in, ase, 1);

	return mlx5_core_access_reg(dev, in, sizeof(in), out,
				    sizeof(out), MLX5_REG_PAOS, 0, 1);
}
