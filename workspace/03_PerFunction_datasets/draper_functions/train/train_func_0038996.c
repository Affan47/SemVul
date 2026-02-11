max77843_muic_jig_handler(struct max77843_muic_info *info,
		int cable_type, bool attached)
{
	int ret;
	u8 path = MAX77843_MUIC_CONTROL1_SW_OPEN;

	dev_dbg(info->dev, "external connector is %s (adc:0x%02x)\n",
			attached ? "attached" : "detached", cable_type);

	switch (cable_type) {
	case MAX77843_MUIC_ADC_FACTORY_MODE_USB_OFF:
	case MAX77843_MUIC_ADC_FACTORY_MODE_USB_ON:
		path = MAX77843_MUIC_CONTROL1_SW_USB;
		break;
	case MAX77843_MUIC_ADC_FACTORY_MODE_UART_OFF:
		path = MAX77843_MUIC_CONTROL1_SW_UART;
		break;
	default:
		return -EINVAL;
	}

	ret = max77843_muic_set_path(info, path, attached);
	if (ret < 0)
		return ret;

	extcon_set_cable_state_(info->edev, EXTCON_JIG, attached);

	return 0;
}
