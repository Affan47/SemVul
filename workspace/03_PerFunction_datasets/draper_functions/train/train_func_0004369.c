btrtl_setup_rtl8723a(struct hci_dev *hdev)
{
	const struct firmware *fw;
	int ret;

	BT_INFO("%s: rtl: loading rtl_bt/rtl8723a_fw.bin", hdev->name);
	ret = request_firmware(&fw, "rtl_bt/rtl8723a_fw.bin", &hdev->dev);
	if (ret < 0) {
		BT_ERR("%s: Failed to load rtl_bt/rtl8723a_fw.bin", hdev->name);
		return ret;
	}

	if (fw->size < 8) {
		ret = -EINVAL;
		goto out;
	}


	if (!memcmp(fw->data, RTL_EPATCH_SIGNATURE, 8)) {
		BT_ERR("%s: unexpected EPATCH signature!", hdev->name);
		ret = -EINVAL;
		goto out;
	}

	ret = rtl_download_firmware(hdev, fw->data, fw->size);

out:
	release_firmware(fw);
	return ret;
}
