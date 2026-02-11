ethtool2ptys_link_modes(u32 link_modes, enum ethtool_report report)
{
	int i;
	u32 ptys_modes = 0;

	for (i = 0; i < MLX4_LINK_MODES_SZ; i++) {
		if (ptys2ethtool_map[i][report] & link_modes)
			ptys_modes |= 1 << i;
	}
	return ptys_modes;
}
