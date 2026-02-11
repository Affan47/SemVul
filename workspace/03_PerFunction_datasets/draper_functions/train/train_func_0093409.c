pinconf_map_to_setting(struct pinctrl_map const *map,
			  struct pinctrl_setting *setting)
{
	struct pinctrl_dev *pctldev = setting->pctldev;
	int pin;

	switch (setting->type) {
	case PIN_MAP_TYPE_CONFIGS_PIN:
		pin = pin_get_from_name(pctldev,
					map->data.configs.group_or_pin);
		if (pin < 0) {
			dev_err(pctldev->dev, "could not map pin config for \"%s\"",
				map->data.configs.group_or_pin);
			return pin;
		}
		setting->data.configs.group_or_pin = pin;
		break;
	case PIN_MAP_TYPE_CONFIGS_GROUP:
		pin = pinctrl_get_group_selector(pctldev,
					 map->data.configs.group_or_pin);
		if (pin < 0) {
			dev_err(pctldev->dev, "could not map group config for \"%s\"",
				map->data.configs.group_or_pin);
			return pin;
		}
		setting->data.configs.group_or_pin = pin;
		break;
	default:
		return -EINVAL;
	}

	setting->data.configs.num_configs = map->data.configs.num_configs;
	setting->data.configs.configs = map->data.configs.configs;

	return 0;
}
