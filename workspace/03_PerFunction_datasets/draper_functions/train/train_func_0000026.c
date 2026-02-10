tonga_populate_single_firmware_entry(struct pp_smumgr *smumgr,
				uint16_t firmware_type,
				struct SMU_Entry *pentry)
{
	int result;
	struct cgs_firmware_info info = {0};

	result = cgs_get_firmware_info(
				smumgr->device,
				tonga_convert_fw_type_to_cgs(firmware_type),
				&info);

	if (result == 0) {
		pentry->version = 0;
		pentry->id = (uint16_t)firmware_type;
		pentry->image_addr_high = smu_upper_32_bits(info.mc_addr);
		pentry->image_addr_low = smu_lower_32_bits(info.mc_addr);
		pentry->meta_data_addr_high = 0;
		pentry->meta_data_addr_low = 0;
		pentry->data_size_byte = info.image_size;
		pentry->num_register_entries = 0;

		if (firmware_type == UCODE_ID_RLC_G)
			pentry->flags = 1;
		else
			pentry->flags = 0;
	} else {
		return result;
	}

	return result;
}
