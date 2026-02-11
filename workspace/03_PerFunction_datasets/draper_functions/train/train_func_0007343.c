AT_GetSMSCenter(gn_data *data, struct gn_statemachine *state)
{

	if (data->message_center && data->message_center->id != 1)
		return GN_ERR_INVALIDLOCATION;
	at_set_charset(data, state, AT_CHAR_GSM);
 	if (sm_message_send(9, GN_OP_GetSMSCenter, "AT+CSCA?\r", state))
		return GN_ERR_NOTREADY;
	return sm_block_no_retry(GN_OP_GetSMSCenter, data, state);
}
