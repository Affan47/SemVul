SetRawRingtone(gn_data *data, struct gn_statemachine *state)
{
	unsigned char req[512] = {0x00, 0x01, 0xa0,
				  0x00,
				  0x00, 0x0c, 0x2c, 0x01, 0x00, 0x00, 0x00, 0x00,
				  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				  0x00, 0x02, 0xfc, 0x09};
	gn_error error;
	int len;

	if (!data || !data->ringtone || !data->raw_data || !data->raw_data->data)
		return GN_ERR_INTERNALERROR;
	if (data->ringtone->location < 0) data->ringtone->location = 17;

	req[3] = data->ringtone->location - 17;
	snprintf(req + 8, 13, "%s", data->ringtone->name);
	if (memcmp(data->raw_data->data, req + 20, 3) == 0) {
		memcpy(req + 20, data->raw_data->data, data->raw_data->length);
		len = 20 + data->raw_data->length;
	} else {

		memcpy(req + 24, data->raw_data->data, data->raw_data->length);
		len = 24 + data->raw_data->length;
	}

	if ((error = pnok_extended_cmds_enable(0x01, data, state))) return error;

	if (sm_message_send(len, 0x40, req, state)) return GN_ERR_NOTREADY;
	return sm_block(0x40, data, state);
}
