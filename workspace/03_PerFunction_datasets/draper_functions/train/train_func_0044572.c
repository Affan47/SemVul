rocker_cmd_get_port_settings_phys_name_proc(const struct rocker_port *rocker_port,
					    const struct rocker_desc_info *desc_info,
					    void *priv)
{
	const struct rocker_tlv *info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_MAX + 1];
	const struct rocker_tlv *attrs[ROCKER_TLV_CMD_MAX + 1];
	struct port_name *name = priv;
	const struct rocker_tlv *attr;
	size_t i, j, len;
	const char *str;

	rocker_tlv_parse_desc(attrs, ROCKER_TLV_CMD_MAX, desc_info);
	if (!attrs[ROCKER_TLV_CMD_INFO])
		return -EIO;

	rocker_tlv_parse_nested(info_attrs, ROCKER_TLV_CMD_PORT_SETTINGS_MAX,
				attrs[ROCKER_TLV_CMD_INFO]);
	attr = info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_PHYS_NAME];
	if (!attr)
		return -EIO;

	len = min_t(size_t, rocker_tlv_len(attr), name->len);
	str = rocker_tlv_data(attr);


	for (i = j = 0; i < len; ++i) {
		if (isalnum(str[i])) {
			name->buf[j] = str[i];
			j++;
		}
	}

	if (j == 0)
		return -EIO;

	name->buf[j] = '\0';

	return 0;
}
