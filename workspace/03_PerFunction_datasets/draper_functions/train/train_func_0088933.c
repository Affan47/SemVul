get_platform_fw_field_metadata(struct hfi1_devdata *dd, int table,
		int field, u32 *field_len_bits, u32 *field_start_bits)
{
	struct platform_config_cache *pcfgcache = &dd->pcfg_cache;
	u32 *src_ptr = NULL;

	if (!pcfgcache->cache_valid)
		return -EINVAL;

	switch (table) {
	case PLATFORM_CONFIG_SYSTEM_TABLE:

	case PLATFORM_CONFIG_PORT_TABLE:

	case PLATFORM_CONFIG_RX_PRESET_TABLE:

	case PLATFORM_CONFIG_TX_PRESET_TABLE:

	case PLATFORM_CONFIG_QSFP_ATTEN_TABLE:

	case PLATFORM_CONFIG_VARIABLE_SETTINGS_TABLE:
		if (field && field < platform_config_table_limits[table])
			src_ptr =
			pcfgcache->config_tables[table].table_metadata + field;
		break;
	default:
		dd_dev_info(dd, "%s: Unknown table\n", __func__);
		break;
	}

	if (!src_ptr)
		return -EINVAL;

	if (field_start_bits)
		*field_start_bits = *src_ptr &
		      ((1 << METADATA_TABLE_FIELD_START_LEN_BITS) - 1);

	if (field_len_bits)
		*field_len_bits = (*src_ptr >> METADATA_TABLE_FIELD_LEN_SHIFT)
		       & ((1 << METADATA_TABLE_FIELD_LEN_LEN_BITS) - 1);

	return 0;
}
