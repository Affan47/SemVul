rocker_cmd_get_port_stats_ethtool_proc(const struct rocker_port *rocker_port,
				       const struct rocker_desc_info *desc_info,
				       void *priv)
{
	const struct rocker_tlv *attrs[ROCKER_TLV_CMD_MAX + 1];
	const struct rocker_tlv *stats_attrs[ROCKER_TLV_CMD_PORT_STATS_MAX + 1];
	const struct rocker_tlv *pattr;
	u32 pport;
	u64 *data = priv;
	int i;

	rocker_tlv_parse_desc(attrs, ROCKER_TLV_CMD_MAX, desc_info);

	if (!attrs[ROCKER_TLV_CMD_INFO])
		return -EIO;

	rocker_tlv_parse_nested(stats_attrs, ROCKER_TLV_CMD_PORT_STATS_MAX,
				attrs[ROCKER_TLV_CMD_INFO]);

	if (!stats_attrs[ROCKER_TLV_CMD_PORT_STATS_PPORT])
		return -EIO;

	pport = rocker_tlv_get_u32(stats_attrs[ROCKER_TLV_CMD_PORT_STATS_PPORT]);
	if (pport != rocker_port->pport)
		return -EIO;

	for (i = 0; i < ARRAY_SIZE(rocker_port_stats); i++) {
		pattr = stats_attrs[rocker_port_stats[i].type];
		if (!pattr)
			continue;

		data[i] = rocker_tlv_get_u64(pattr);
	}

	return 0;
}
