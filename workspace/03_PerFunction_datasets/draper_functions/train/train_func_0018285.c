max14577_muic_jig_handler(struct max14577_muic_info *info,
		int cable_type, bool attached)
{
	int ret = 0;
	u8 path = CTRL1_SW_OPEN;

	dev_dbg(info->dev,
		"external connector is %s (adc:0x%02x)\n",
		attached ? "attached" : "detached", cable_type);

	switch (cable_type) {
	case MAX14577_MUIC_ADC_FACTORY_MODE_USB_OFF:
	case MAX14577_MUIC_ADC_FACTORY_MODE_USB_ON:

		path = CTRL1_SW_USB;
		break;
	case MAX14577_MUIC_ADC_FACTORY_MODE_UART_OFF:

		path = CTRL1_SW_UART;
		break;
	default:
		dev_err(info->dev, "failed to detect %s jig cable\n",
			attached ? "attached" : "detached");
		return -EINVAL;
	}

	ret = max14577_muic_set_path(info, path, attached);
	if (ret < 0)
		return ret;

	extcon_set_cable_state_(info->edev, EXTCON_JIG, attached);

	return 0;
}
