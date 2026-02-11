mwifiex_usb_data_sent(struct mwifiex_adapter *adapter)
{
	struct usb_card_rec *card = adapter->card;
	int i;

	for (i = 0; i < MWIFIEX_TX_DATA_PORT; i++)
		if (!card->port[i].block_status)
			return false;

	return true;
}
