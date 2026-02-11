AT_DeleteSMS(gn_data *data, struct gn_statemachine *state)
{
	unsigned char req[32];
	gn_error err;

	err = AT_SetSMSMemoryType(data->raw_sms->memory_type,  state);
	if (err)
		return err;
	snprintf(req, sizeof(req), "AT+CMGD=%d\r", data->sms->number);

	if (sm_message_send(strlen(req), GN_OP_DeleteSMS, req, state))
 		return GN_ERR_NOTREADY;
	return sm_block_no_retry(GN_OP_DeleteSMS, data, state);
}
