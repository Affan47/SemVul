max77693_led_get_configuration(struct max77693_led_device *led,
				struct max77693_led_config_data *cfg,
				struct device_node **sub_nodes)
{
	int ret;

	ret = max77693_led_parse_dt(led, cfg, sub_nodes);
	if (ret < 0)
		return ret;

	max77693_led_validate_configuration(led, cfg);

	memcpy(led->iout_torch_max, cfg->iout_torch_max,
				sizeof(led->iout_torch_max));
	memcpy(led->iout_flash_max, cfg->iout_flash_max,
				sizeof(led->iout_flash_max));

	return 0;
}
