P3110_GetPhoneInfo(gn_data *data, struct gn_statemachine *state)
{
	dprintf("Getting phone info...\n");
	if (sm_message_send(0, 0x4c, NULL, state) != GN_ERR_NONE) return GN_ERR_NOTREADY;
	return sm_block(0x4d, data, state);
}
