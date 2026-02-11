NK7110_GetSMSnoValidate(gn_data *data, struct gn_statemachine *state)
{
	unsigned char req[] = {FBUS_FRAME_HEADER, 0x07,
				0x08,
				0x00,
				0x01,
				0x01, 0x65, 0x01};

	req[4] = get_memory_type(data->raw_sms->memory_type);
	req[5] = (data->raw_sms->number & 0xff00) >> 8;
	req[6] = data->raw_sms->number & 0x00ff;
	SEND_MESSAGE_BLOCK(NK7110_MSG_FOLDER, 10);
}
