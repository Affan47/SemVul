set_l2_table_entry_cmd(struct mlx5_core_dev *dev, u32 index,
				  u8 *mac, u8 vlan_valid, u16 vlan)
{
	u32 in[MLX5_ST_SZ_DW(set_l2_table_entry_in)];
	u32 out[MLX5_ST_SZ_DW(set_l2_table_entry_out)];
	u8 *in_mac_addr;

	memset(in, 0, sizeof(in));
	memset(out, 0, sizeof(out));

	MLX5_SET(set_l2_table_entry_in, in, opcode,
		 MLX5_CMD_OP_SET_L2_TABLE_ENTRY);
	MLX5_SET(set_l2_table_entry_in, in, table_index, index);
	MLX5_SET(set_l2_table_entry_in, in, vlan_valid, vlan_valid);
	MLX5_SET(set_l2_table_entry_in, in, vlan, vlan);

	in_mac_addr = MLX5_ADDR_OF(set_l2_table_entry_in, in, mac_address);
	ether_addr_copy(&in_mac_addr[2], mac);

	return mlx5_cmd_exec_check_status(dev, in, sizeof(in),
					  out, sizeof(out));
}
