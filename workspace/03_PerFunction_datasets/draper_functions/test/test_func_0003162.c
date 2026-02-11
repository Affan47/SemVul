max77843_muic_adc_gnd_handler(struct max77843_muic_info *info)
{
	int ret, gnd_cable_type;
	bool attached;

	gnd_cable_type = max77843_muic_get_cable_type(info,
			MAX77843_CABLE_GROUP_ADC_GND, &attached);
	dev_dbg(info->dev, "external connector is %s (gnd:0x%02x)\n",
			attached ? "attached" : "detached", gnd_cable_type);

	switch (gnd_cable_type) {
	case MAX77843_MUIC_GND_USB_HOST:
	case MAX77843_MUIC_GND_USB_HOST_VB:
		ret = max77843_muic_set_path(info,
					     MAX77843_MUIC_CONTROL1_SW_USB,
					     attached);
		if (ret < 0)
			return ret;

		extcon_set_cable_state_(info->edev, EXTCON_USB_HOST, attached);
		break;
	case MAX77843_MUIC_GND_MHL_VB:
	case MAX77843_MUIC_GND_MHL:
		ret = max77843_muic_set_path(info,
					     MAX77843_MUIC_CONTROL1_SW_OPEN,
					     attached);
		if (ret < 0)
			return ret;

		extcon_set_cable_state_(info->edev, EXTCON_DISP_MHL, attached);
		break;
	default:
		dev_err(info->dev, "failed to detect %s accessory(gnd:0x%x)\n",
			attached ? "attached" : "detached", gnd_cable_type);
		return -EINVAL;
	}

	return 0;
}
