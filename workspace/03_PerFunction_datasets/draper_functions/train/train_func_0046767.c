rt2x00usb_clear_entry(struct queue_entry *entry)
{
	entry->flags = 0;

	if (entry->queue->qid == QID_RX)
		rt2x00usb_kick_rx_entry(entry, NULL);
}
