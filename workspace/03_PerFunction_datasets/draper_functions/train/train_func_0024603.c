NK6510_SetDateTime(gn_data *data, struct gn_statemachine *state)
{
	unsigned char req[] = {FBUS_FRAME_HEADER, 0x01, 0x00, 0x01,
			       0x01, 0x0c, 0x01, 0x03,
			       0x07, 0xd2,
			       0x08, 0x01,
			       0x15, 0x1f,
			       0x00,
			       0x00};

	req[10] = data->datetime->year / 256;
	req[11] = data->datetime->year % 256;
	req[12] = data->datetime->month;
	req[13] = data->datetime->day;
	req[14] = data->datetime->hour;
	req[15] = data->datetime->minute;
	req[16] = data->datetime->second;

	SEND_MESSAGE_BLOCK(NK6510_MSG_CLOCK, 18);
}
