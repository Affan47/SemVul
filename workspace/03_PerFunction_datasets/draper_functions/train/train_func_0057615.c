AT_GetRevision(gn_data *data, struct gn_statemachine *state)
{
	gn_error err;

	if (sm_message_send(8, GN_OP_Identify, "AT+CGMR\r", state))
		return GN_ERR_NOTREADY;
	if ((err = sm_block_no_retry(GN_OP_Identify, data, state)) == GN_ERR_NONE)
		return GN_ERR_NONE;

	if (sm_message_send(7, GN_OP_Identify, "AT+GMR\r", state))
		return GN_ERR_NOTREADY;
	if (sm_block_no_retry(GN_OP_Identify, data, state) == GN_ERR_NONE)
		return GN_ERR_NONE;

	return err;
}
