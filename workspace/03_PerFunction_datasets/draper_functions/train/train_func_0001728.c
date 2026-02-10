fm_power_up(struct fmdev *fmdev, u8 mode)
{
	u16 payload;
	__be16 asic_id, asic_ver;
	int resp_len, ret;
	u8 fw_name[50];

	if (mode >= FM_MODE_ENTRY_MAX) {
		fmerr("Invalid firmware download option\n");
		return -EINVAL;
	}


	ret = fmc_prepare(fmdev);
	if (ret < 0) {
		fmerr("Unable to prepare FM Common\n");
		return ret;
	}

	payload = FM_ENABLE;
	if (fmc_send_cmd(fmdev, FM_POWER_MODE, REG_WR, &payload,
			sizeof(payload), NULL, NULL))
		goto rel;


	msleep(20);

	if (fmc_send_cmd(fmdev, ASIC_ID_GET, REG_RD, NULL,
			sizeof(asic_id), &asic_id, &resp_len))
		goto rel;

	if (fmc_send_cmd(fmdev, ASIC_VER_GET, REG_RD, NULL,
			sizeof(asic_ver), &asic_ver, &resp_len))
		goto rel;

	fmdbg("ASIC ID: 0x%x , ASIC Version: %d\n",
		be16_to_cpu(asic_id), be16_to_cpu(asic_ver));

	sprintf(fw_name, "%s_%x.%d.bts", FM_FMC_FW_FILE_START,
		be16_to_cpu(asic_id), be16_to_cpu(asic_ver));

	ret = fm_download_firmware(fmdev, fw_name);
	if (ret < 0) {
		fmdbg("Failed to download firmware file %s\n", fw_name);
		goto rel;
	}
	sprintf(fw_name, "%s_%x.%d.bts", (mode == FM_MODE_RX) ?
			FM_RX_FW_FILE_START : FM_TX_FW_FILE_START,
			be16_to_cpu(asic_id), be16_to_cpu(asic_ver));

	ret = fm_download_firmware(fmdev, fw_name);
	if (ret < 0) {
		fmdbg("Failed to download firmware file %s\n", fw_name);
		goto rel;
	} else
		return ret;
rel:
	return fmc_release(fmdev);
}
