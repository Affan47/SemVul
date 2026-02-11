ath9k_hif_usb_firmware_cb(const struct firmware *fw, void *context)
{
	struct hif_device_usb *hif_dev = context;
	int ret;

	if (!fw) {
		ret = ath9k_hif_request_firmware(hif_dev, false);
		if (!ret)
			return;

		dev_err(&hif_dev->udev->dev,
			"ath9k_htc: Failed to get firmware %s\n",
			hif_dev->fw_name);
		goto err_fw;
	}

	hif_dev->htc_handle = ath9k_htc_hw_alloc(hif_dev, &hif_usb,
						 &hif_dev->udev->dev);
	if (hif_dev->htc_handle == NULL)
		goto err_dev_alloc;

	hif_dev->fw_data = fw->data;
	hif_dev->fw_size = fw->size;


	ret = ath9k_hif_usb_dev_init(hif_dev);
	if (ret)
		goto err_dev_init;

	ret = ath9k_htc_hw_init(hif_dev->htc_handle,
				&hif_dev->interface->dev,
				hif_dev->usb_device_id->idProduct,
				hif_dev->udev->product,
				hif_dev->usb_device_id->driver_info);
	if (ret) {
		ret = -EINVAL;
		goto err_htc_hw_init;
	}

	release_firmware(fw);
	hif_dev->flags |= HIF_USB_READY;
	complete_all(&hif_dev->fw_done);

	return;

err_htc_hw_init:
	ath9k_hif_usb_dev_deinit(hif_dev);
err_dev_init:
	ath9k_htc_hw_free(hif_dev->htc_handle);
err_dev_alloc:
	release_firmware(fw);
err_fw:
	ath9k_hif_usb_firmware_fail(hif_dev);
}
