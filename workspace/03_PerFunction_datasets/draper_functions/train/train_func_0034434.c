NK6510_AnswerCall(gn_data *data, struct gn_statemachine *state)
{
	unsigned char req[] = {FBUS_FRAME_HEADER, 0x06, 0x00};

	if (!data->call_info)
		return GN_ERR_INTERNALERROR;

	req[4] = data->call_info->call_id;

	if (sm_message_send(5, NK6510_MSG_COMMSTATUS, req, state))
		return GN_ERR_NOTREADY;
	return sm_block_ack(state);
}
