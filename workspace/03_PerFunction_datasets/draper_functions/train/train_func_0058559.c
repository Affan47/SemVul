aesX660_dev_deactivate(struct fp_img_dev *dev)
{
	struct aesX660_dev *aesdev = dev->priv;

	if (aesdev->fd_data_transfer)
		libusb_cancel_transfer(aesdev->fd_data_transfer);

	aesdev->deactivating = TRUE;
}
