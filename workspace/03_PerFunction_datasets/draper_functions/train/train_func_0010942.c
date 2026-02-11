send_packet(struct btdev *btdev, const void *data, uint16_t len)
{
	if (!btdev->send_handler)
		return;

	btdev->send_handler(data, len, btdev->send_data);
}
