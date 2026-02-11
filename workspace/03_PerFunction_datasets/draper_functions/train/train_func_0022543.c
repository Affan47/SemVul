ptys2ethtool_link_modes(u32 eth_proto, enum ethtool_report report)
{
	int i;
	u32 link_modes = 0;

	for (i = 0; i < MLX4_LINK_MODES_SZ; i++) {
		if (eth_proto & MLX4_PROT_MASK(i))
			link_modes |= ptys2ethtool_map[i][report];
	}
	return link_modes;
}
