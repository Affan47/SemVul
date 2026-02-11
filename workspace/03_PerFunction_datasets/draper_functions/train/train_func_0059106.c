NK6510_Identify(gn_data *data, struct gn_statemachine *state)
{
	unsigned char req[] = {FBUS_FRAME_HEADER, 0x00, 0x41};
	unsigned char req2[] = {FBUS_FRAME_HEADER, 0x07, 0x01, 0x00};
	gn_error err;

	dprintf("Identifying...\n");
	pnok_manufacturer_get(data->manufacturer);
	if (sm_message_send(5, 0x1b, req, state)) return GN_ERR_NOTREADY;
	if (sm_message_send(6, 0x1b, req2, state)) return GN_ERR_NOTREADY;
	sm_wait_for(0x1b, data, state);
	sm_block(0x1b, data, state);
	err = sm_error_get(0x1b, state);
	if (err != GN_ERR_NONE) return err;


	if (gn_sm_loop(0, state) != GN_SM_Initialised) return GN_ERR_UNKNOWN;
	return GN_ERR_NONE;
}
