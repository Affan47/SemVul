bfusb_flush(struct hci_dev *hdev)
{
	struct bfusb_data *data = hci_get_drvdata(hdev);

	BT_DBG("hdev %p bfusb %p", hdev, data);

	skb_queue_purge(&data->transmit_q);

	return 0;
}
