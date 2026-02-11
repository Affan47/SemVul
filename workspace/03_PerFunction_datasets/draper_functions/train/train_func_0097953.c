_get_update_config_stages(int noreset)
{
	std::vector<uint32_t> stages;
	uint32_t *base_stages;
	int num_base_stages;

	if (is_z_remote() || is_mh_remote()) {
		base_stages = (uint32_t*)update_configuration_zwave_mh_stages;
		num_base_stages = update_configuration_zwave_mh_num_stages;
	} else {
		base_stages = (uint32_t*)update_configuration_hid_stages;
		num_base_stages = update_configuration_hid_num_stages;
	}

	for (int i = 0; i < num_base_stages; i++)
		stages.push_back(base_stages[i]);

	if (!noreset && !(is_z_remote() && !is_usbnet_remote()))
		stages.push_back(LC_CB_STAGE_RESET);

	stages.push_back(LC_CB_STAGE_SET_TIME);

	return stages;
}
