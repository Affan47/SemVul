sci_remote_node_table_get_group_index(
	struct sci_remote_node_table *remote_node_table,
	u32 group_table_index)
{
	u32 dword_index;
	u32 *group_table;
	u32 bit_index;

	group_table = remote_node_table->remote_node_groups[group_table_index];

	for (dword_index = 0; dword_index < remote_node_table->group_array_size; dword_index++) {
		if (group_table[dword_index] != 0) {
			for (bit_index = 0; bit_index < 32; bit_index++) {
				if ((group_table[dword_index] & (1 << bit_index)) != 0) {
					return (dword_index * 32) + bit_index;
				}
			}
		}
	}

	return SCIC_SDS_REMOTE_NODE_TABLE_INVALID_INDEX;
}
