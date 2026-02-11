cz_smu_populate_firmware_entries(struct pp_smumgr *smumgr)
{
	struct cz_smumgr *cz_smu = (struct cz_smumgr *)smumgr->backend;
	uint32_t firmware_type;
	uint32_t i;
	int ret;
	enum cgs_ucode_id ucode_id;
	struct cgs_firmware_info info = {0};

	cz_smu->driver_buffer_length = 0;

	for (i = 0; i < sizeof(firmware_list)/sizeof(*firmware_list); i++) {

		firmware_type = cz_translate_firmware_enum_to_arg(smumgr,
					firmware_list[i]);

		ucode_id = cz_convert_fw_type_to_cgs(firmware_type);

		ret = cgs_get_firmware_info(smumgr->device,
							ucode_id, &info);

		if (ret == 0) {
			cz_smu->driver_buffer[i].mc_addr_high =
					smu_upper_32_bits(info.mc_addr);

			cz_smu->driver_buffer[i].mc_addr_low =
					smu_lower_32_bits(info.mc_addr);

			cz_smu->driver_buffer[i].data_size = info.image_size;

			cz_smu->driver_buffer[i].firmware_ID = firmware_list[i];
			cz_smu->driver_buffer_length++;
		}
	}

	return 0;
}
