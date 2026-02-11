cyapa_pip_state_parse(struct cyapa *cyapa, u8 *reg_data, int len)
{
	u8 cmd[] = { 0x01, 0x00};
	struct pip_fixed_info pip_info;
	u8 resp_data[PIP_HID_DESCRIPTOR_SIZE];
	int resp_len;
	bool is_bootloader;
	int error;

	cyapa->state = CYAPA_STATE_NO_DEVICE;


	cyapa_pip_deep_sleep(cyapa, PIP_DEEP_SLEEP_STATE_ON);


	cyapa_empty_pip_output_data(cyapa, NULL, NULL, NULL);


	resp_len = PIP_HID_DESCRIPTOR_SIZE;
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
			cmd, sizeof(cmd),
			resp_data, &resp_len,
			300,
			cyapa_sort_pip_hid_descriptor_data,
			false);
	if (error)
		return error;

	if (resp_data[PIP_RESP_REPORT_ID_OFFSET] == PIP_HID_BL_REPORT_ID)
		is_bootloader = true;
	else if (resp_data[PIP_RESP_REPORT_ID_OFFSET] == PIP_HID_APP_REPORT_ID)
		is_bootloader = false;
	else
		return -EAGAIN;


	memset(&pip_info, 0, sizeof(struct pip_fixed_info));
	error = cyapa_get_pip_fixed_info(cyapa, &pip_info, is_bootloader);
	if (error)
		return error;

	if (pip_info.family_id == 0x9B && pip_info.silicon_id_high == 0x0B) {
		cyapa->gen = CYAPA_GEN6;
		cyapa->state = is_bootloader ? CYAPA_STATE_GEN6_BL
					     : CYAPA_STATE_GEN6_APP;
	} else if (pip_info.family_id == 0x91 &&
		   pip_info.silicon_id_high == 0x02) {
		cyapa->gen = CYAPA_GEN5;
		cyapa->state = is_bootloader ? CYAPA_STATE_GEN5_BL
					     : CYAPA_STATE_GEN5_APP;
	}

	return 0;
}
