is_ext_fw_info_supported(uint16_t device_id) {
	int i;
	for (i = 0; ext_fw_info_device[i][0]; i++)
		if (ext_fw_info_device[i][0] <= device_id &&
		    device_id <= ext_fw_info_device[i][1])
			return 1;
	return 0;
}
