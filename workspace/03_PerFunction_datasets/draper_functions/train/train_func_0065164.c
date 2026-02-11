max8997_muic_adc_handler(struct max8997_muic_info *info)
{
	int cable_type;
	bool attached;
	int ret = 0;


	cable_type = max8997_muic_get_cable_type(info,
				MAX8997_CABLE_GROUP_ADC, &attached);

	switch (cable_type) {
	case MAX8997_MUIC_ADC_GROUND:
		ret = max8997_muic_handle_usb(info, MAX8997_USB_HOST, attached);
		if (ret < 0)
			return ret;
		break;
	case MAX8997_MUIC_ADC_MHL:
		extcon_set_cable_state_(info->edev, EXTCON_DISP_MHL, attached);
		break;
	case MAX8997_MUIC_ADC_FACTORY_MODE_USB_OFF:
	case MAX8997_MUIC_ADC_FACTORY_MODE_USB_ON:
		ret = max8997_muic_handle_usb(info,
					     MAX8997_USB_DEVICE, attached);
		if (ret < 0)
			return ret;
		break;
	case MAX8997_MUIC_ADC_AV_CABLE_NOLOAD:
	case MAX8997_MUIC_ADC_FACTORY_MODE_UART_ON:
		ret = max8997_muic_handle_dock(info, cable_type, attached);
		if (ret < 0)
			return ret;
		break;
	case MAX8997_MUIC_ADC_FACTORY_MODE_UART_OFF:
		ret = max8997_muic_handle_jig_uart(info, attached);
		break;
	case MAX8997_MUIC_ADC_REMOTE_S1_BUTTON:
	case MAX8997_MUIC_ADC_REMOTE_S2_BUTTON:
	case MAX8997_MUIC_ADC_REMOTE_S3_BUTTON:
	case MAX8997_MUIC_ADC_REMOTE_S4_BUTTON:
	case MAX8997_MUIC_ADC_REMOTE_S5_BUTTON:
	case MAX8997_MUIC_ADC_REMOTE_S6_BUTTON:
	case MAX8997_MUIC_ADC_REMOTE_S7_BUTTON:
	case MAX8997_MUIC_ADC_REMOTE_S8_BUTTON:
	case MAX8997_MUIC_ADC_REMOTE_S9_BUTTON:
	case MAX8997_MUIC_ADC_REMOTE_S10_BUTTON:
	case MAX8997_MUIC_ADC_REMOTE_S11_BUTTON:
	case MAX8997_MUIC_ADC_REMOTE_S12_BUTTON:
	case MAX8997_MUIC_ADC_RESERVED_ACC_1:
	case MAX8997_MUIC_ADC_RESERVED_ACC_2:
	case MAX8997_MUIC_ADC_RESERVED_ACC_3:
	case MAX8997_MUIC_ADC_RESERVED_ACC_4:
	case MAX8997_MUIC_ADC_RESERVED_ACC_5:
	case MAX8997_MUIC_ADC_CEA936_AUDIO:
	case MAX8997_MUIC_ADC_PHONE_POWERED_DEV:
	case MAX8997_MUIC_ADC_TTY_CONVERTER:
	case MAX8997_MUIC_ADC_UART_CABLE:
	case MAX8997_MUIC_ADC_CEA936A_TYPE1_CHG:
	case MAX8997_MUIC_ADC_CEA936A_TYPE2_CHG:
	case MAX8997_MUIC_ADC_AUDIO_MODE_REMOTE:


		dev_info(info->dev,
			"cable is %s but it isn't used (type:0x%x)\n",
			attached ? "attached" : "detached", cable_type);
		return -EAGAIN;
	default:
		dev_err(info->dev,
			"failed to detect %s unknown cable (type:0x%x)\n",
			attached ? "attached" : "detached", cable_type);
		return -EINVAL;
	}

	return 0;
}
