NK6510_WriteWAPBookmark(gn_data *data, struct gn_statemachine *state)
{
	unsigned char req[350] = { FBUS_FRAME_HEADER, 0x09,
				0xFF, 0xFF};
	gn_error error;
	int pos = 6;

	dprintf("Writing WAP bookmark\n");

	if (PrepareWAP(data, state) != GN_ERR_NONE) {
		FinishWAP(data, state);
		if ((error = PrepareWAP(data, state))) return error;
	}

	pos += PackWAPString(req + pos, data->wap_bookmark->name, 2);
	pos += PackWAPString(req + pos, data->wap_bookmark->URL, 2);

	if (sm_message_send(pos, NK6510_MSG_WAP, req, state)) return GN_ERR_NOTREADY;
	error = sm_block(NK6510_MSG_WAP, data, state);
	if (error) return error;

	return FinishWAP(data, state);
}
