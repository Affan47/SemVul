get_bitmap_startup_slice(gn_data *data, struct gn_statemachine *state, int s)
{
	nk6160_driver_instance *drvinst = NK6160_DRVINST(state);
	unsigned char req[] = {0x00, 0x01, 0x07, 0x07, 0x08, 0x00};

	drvinst->logoslice = s;
	req[5] = (unsigned char)s + 1;
	SEND_MESSAGE_BLOCK(0x40, 6);
}
