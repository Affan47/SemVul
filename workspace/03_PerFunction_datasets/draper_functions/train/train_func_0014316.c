lpfc_sli4_request_firmware_update(struct lpfc_hba *phba, uint8_t fw_upgrade)
{
	uint8_t file_name[ELX_MODEL_NAME_SIZE];
	int ret;
	const struct firmware *fw;


	if (bf_get(lpfc_sli_intf_if_type, &phba->sli4_hba.sli_intf) !=
	    LPFC_SLI_INTF_IF_TYPE_2)
		return -EPERM;

	snprintf(file_name, ELX_MODEL_NAME_SIZE, "%s.grp", phba->ModelName);

	if (fw_upgrade == INT_FW_UPGRADE) {
		ret = request_firmware_nowait(THIS_MODULE, FW_ACTION_HOTPLUG,
					file_name, &phba->pcidev->dev,
					GFP_KERNEL, (void *)phba,
					lpfc_write_firmware);
	} else if (fw_upgrade == RUN_FW_UPGRADE) {
		ret = request_firmware(&fw, file_name, &phba->pcidev->dev);
		if (!ret)
			lpfc_write_firmware(fw, (void *)phba);
	} else {
		ret = -EINVAL;
	}

	return ret;
}
