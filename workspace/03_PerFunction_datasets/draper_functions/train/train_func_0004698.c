mlx5_core_query_rmp(struct mlx5_core_dev *dev, u32 rmpn, u32 *out)
{
	u32 in[MLX5_ST_SZ_DW(query_rmp_in)];
	int outlen = MLX5_ST_SZ_BYTES(query_rmp_out);

	memset(in, 0, sizeof(in));
	MLX5_SET(query_rmp_in, in, opcode, MLX5_CMD_OP_QUERY_RMP);
	MLX5_SET(query_rmp_in, in, rmpn,   rmpn);

	return mlx5_cmd_exec_check_status(dev, in, sizeof(in), out, outlen);
}
