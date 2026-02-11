btsdio_probe(struct sdio_func *func,
				const struct sdio_device_id *id)
{
	struct btsdio_data *data;
	struct hci_dev *hdev;
	struct sdio_func_tuple *tuple = func->tuples;
	int err;

	BT_DBG("func %p id %p class 0x%04x", func, id, func->class);

	while (tuple) {
		BT_DBG("code 0x%x size %d", tuple->code, tuple->size);
		tuple = tuple->next;
	}

	data = devm_kzalloc(&func->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->func = func;

	INIT_WORK(&data->work, btsdio_work);

	skb_queue_head_init(&data->txq);

	hdev = hci_alloc_dev();
	if (!hdev)
		return -ENOMEM;

	hdev->bus = HCI_SDIO;
	hci_set_drvdata(hdev, data);

	if (id->class == SDIO_CLASS_BT_AMP)
		hdev->dev_type = HCI_AMP;
	else
		hdev->dev_type = HCI_BREDR;

	data->hdev = hdev;

	SET_HCIDEV_DEV(hdev, &func->dev);

	hdev->open     = btsdio_open;
	hdev->close    = btsdio_close;
	hdev->flush    = btsdio_flush;
	hdev->send     = btsdio_send_frame;

	if (func->vendor == 0x0104 && func->device == 0x00c5)
		set_bit(HCI_QUIRK_RESET_ON_CLOSE, &hdev->quirks);

	err = hci_register_dev(hdev);
	if (err < 0) {
		hci_free_dev(hdev);
		return err;
	}

	sdio_set_drvdata(func, data);

	return 0;
}
