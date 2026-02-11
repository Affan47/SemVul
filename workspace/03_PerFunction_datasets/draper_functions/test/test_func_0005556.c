mwifiex_usb_dnld_fw(struct mwifiex_adapter *adapter,
			struct mwifiex_fw_image *fw)
{
	int ret;
	struct usb_card_rec *card = (struct usb_card_rec *)adapter->card;

	if (card->usb_boot_state == USB8XXX_FW_DNLD) {
		ret = mwifiex_prog_fw_w_helper(adapter, fw);
		if (ret)
			return -1;


		if (card->usb_boot_state == USB8XXX_FW_DNLD)
			return -1;
	}

	ret = mwifiex_usb_rx_init(adapter);
	if (!ret)
		ret = mwifiex_usb_tx_init(adapter);

	return ret;
}
