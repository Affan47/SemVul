NK7110_PressKey(gn_data *data, struct gn_statemachine *state)
{
	unsigned char req[] = {0x00, 0x01, 0x46, 0x00, 0x01,
			       0x0a};

	dprintf("Pressing key...\n");
	req[5] = data->key_code;
	if (sm_message_send(6, NK7110_MSG_KEYPRESS, req, state)) return GN_ERR_NOTREADY;
	return sm_block(NK7110_MSG_KEYPRESS_RESP, data, state);
}
