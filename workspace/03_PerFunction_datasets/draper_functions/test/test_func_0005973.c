ath3k_load_patch(struct usb_device *udev)
{
	unsigned char fw_state;
	char filename[ATH3K_NAME_LEN] = {0};
	const struct firmware *firmware;
	struct ath3k_version fw_version;
	__u32 pt_rom_version, pt_build_version;
	int ret;

	ret = ath3k_get_state(udev, &fw_state);
	if (ret < 0) {
		BT_ERR("Can't get state to change to load ram patch err");
		return ret;
	}

	if (fw_state & ATH3K_PATCH_UPDATE) {
		BT_DBG("Patch was already downloaded");
		return 0;
	}

	ret = ath3k_get_version(udev, &fw_version);
	if (ret < 0) {
		BT_ERR("Can't get version to change to load ram patch err");
		return ret;
	}

	snprintf(filename, ATH3K_NAME_LEN, "ar3k/AthrBT_0x%08x.dfu",
		 le32_to_cpu(fw_version.rom_version));

	ret = request_firmware(&firmware, filename, &udev->dev);
	if (ret < 0) {
		BT_ERR("Patch file not found %s", filename);
		return ret;
	}

	pt_rom_version = get_unaligned_le32(firmware->data +
					    firmware->size - 8);
	pt_build_version = get_unaligned_le32(firmware->data +
					      firmware->size - 4);

	if (pt_rom_version != le32_to_cpu(fw_version.rom_version) ||
	    pt_build_version <= le32_to_cpu(fw_version.build_version)) {
		BT_ERR("Patch file version did not match with firmware");
		release_firmware(firmware);
		return -EINVAL;
	}

	ret = ath3k_load_fwfile(udev, firmware);
	release_firmware(firmware);

	return ret;
}
