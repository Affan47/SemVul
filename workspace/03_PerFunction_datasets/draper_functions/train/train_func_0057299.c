ds_read_byte(struct ds_device *dev, u8 *byte)
{
	int err;
	struct ds_status st;

	err = ds_send_control(dev, COMM_BYTE_IO | COMM_IM , 0xff);
	if (err)
		return err;

	ds_wait_status(dev, &st);

	err = ds_recv_data(dev, byte, sizeof(*byte));
	if (err < 0)
		return err;

	return 0;
}
