cyapa_pip_check_fw(struct cyapa *cyapa, const struct firmware *fw)
{
	struct device *dev = &cyapa->client->dev;
	struct cyapa_tsg_bin_image_data_record *image_records;
	const struct cyapa_tsg_bin_image_data_record *app_integrity;
	const struct tsg_bl_metadata_row_params *metadata;
	int flash_records_count;
	u32 fw_app_start, fw_upgrade_start;
	u16 fw_app_len, fw_upgrade_len;
	u16 app_crc;
	u16 app_integrity_crc;
	int i;


	if (cyapa_pip_fw_head_check(cyapa,
		(struct cyapa_tsg_bin_image_head *)fw->data)) {
		dev_err(dev, "%s: firmware image not match TP device.\n",
			     __func__);
		return -EINVAL;
	}

	image_records =
		cyapa_get_image_record_data_num(fw, &flash_records_count);


	app_integrity = &image_records[flash_records_count - 1];

	if (app_integrity->flash_array_id != 0x00 ||
	    get_unaligned_be16(&app_integrity->row_number) != 0x01ff) {
		dev_err(dev, "%s: invalid app_integrity data.\n", __func__);
		return -EINVAL;
	}

	metadata = (const void *)app_integrity->record_data;


	app_integrity_crc = crc_itu_t(0xffff, app_integrity->record_data,
				      CYAPA_TSG_APP_INTEGRITY_SIZE);
	if (app_integrity_crc != get_unaligned_le16(&metadata->metadata_crc)) {
		dev_err(dev, "%s: invalid app_integrity crc.\n", __func__);
		return -EINVAL;
	}

	fw_app_start = get_unaligned_le32(&metadata->app_start);
	fw_app_len = get_unaligned_le16(&metadata->app_len);
	fw_upgrade_start = get_unaligned_le32(&metadata->upgrade_start);
	fw_upgrade_len = get_unaligned_le16(&metadata->upgrade_len);

	if (fw_app_start % CYAPA_TSG_FW_ROW_SIZE ||
	    fw_app_len % CYAPA_TSG_FW_ROW_SIZE ||
	    fw_upgrade_start % CYAPA_TSG_FW_ROW_SIZE ||
	    fw_upgrade_len % CYAPA_TSG_FW_ROW_SIZE) {
		dev_err(dev, "%s: invalid image alignment.\n", __func__);
		return -EINVAL;
	}


	app_crc = 0xffffU;
	for (i = 0; i < fw_app_len / CYAPA_TSG_FW_ROW_SIZE; i++) {
		const u8 *data = image_records[i].record_data;

		app_crc = crc_itu_t(app_crc, data, CYAPA_TSG_FW_ROW_SIZE);
	}

	if (app_crc != get_unaligned_le16(&metadata->app_crc)) {
		dev_err(dev, "%s: invalid firmware app crc check.\n", __func__);
		return -EINVAL;
	}

	return 0;
}
