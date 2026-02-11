s5p_mfc_load_firmware(struct s5p_mfc_dev *dev)
{
	struct firmware *fw_blob;
	int i, err = -EINVAL;


	mfc_debug_enter();

	for (i = MFC_FW_MAX_VERSIONS - 1; i >= 0; i--) {
		if (!dev->variant->fw_name[i])
			continue;
		err = request_firmware((const struct firmware **)&fw_blob,
				dev->variant->fw_name[i], dev->v4l2_dev.dev);
		if (!err) {
			dev->fw_ver = (enum s5p_mfc_fw_ver) i;
			break;
		}
	}

	if (err != 0) {
		mfc_err("Firmware is not present in the /lib/firmware directory nor compiled in kernel\n");
		return -EINVAL;
	}
	if (fw_blob->size > dev->fw_size) {
		mfc_err("MFC firmware is too big to be loaded\n");
		release_firmware(fw_blob);
		return -ENOMEM;
	}
	if (!dev->fw_virt_addr) {
		mfc_err("MFC firmware is not allocated\n");
		release_firmware(fw_blob);
		return -EINVAL;
	}
	memcpy(dev->fw_virt_addr, fw_blob->data, fw_blob->size);
	wmb();
	release_firmware(fw_blob);
	mfc_debug_leave();
	return 0;
}
