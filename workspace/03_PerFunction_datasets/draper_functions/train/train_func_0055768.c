mbox_test_receive_message(struct mbox_client *client, void *message)
{
	struct mbox_test_device *tdev = dev_get_drvdata(client->dev);
	unsigned long flags;

	spin_lock_irqsave(&tdev->lock, flags);
	if (tdev->mmio) {
		memcpy_fromio(tdev->rx_buffer, tdev->mmio, MBOX_MAX_MSG_LEN);
		print_hex_dump(KERN_INFO, "Client: Received [MMIO]: ",
			       DUMP_PREFIX_ADDRESS, MBOX_BYTES_PER_LINE, 1,
			       tdev->rx_buffer, MBOX_MAX_MSG_LEN, true);
	} else if (message) {
		print_hex_dump(KERN_INFO, "Client: Received [API]: ",
			       DUMP_PREFIX_ADDRESS, MBOX_BYTES_PER_LINE, 1,
			       message, MBOX_MAX_MSG_LEN, true);
		memcpy(tdev->rx_buffer, message, MBOX_MAX_MSG_LEN);
	}
	spin_unlock_irqrestore(&tdev->lock, flags);
}
