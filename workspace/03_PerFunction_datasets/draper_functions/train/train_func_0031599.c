oct_set_config_info(int oct_id, int conf_type)
{
	if (conf_type < 0 || conf_type > (NUM_OCTEON_CONFS - 1))
		conf_type = OCTEON_CONFIG_TYPE_DEFAULT;
	oct_conf_info[oct_id].conf_type = conf_type;
}
