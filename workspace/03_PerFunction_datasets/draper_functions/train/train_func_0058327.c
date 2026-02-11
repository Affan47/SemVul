AT_OnSMS(gn_data *data, struct gn_statemachine *state)
{
	at_driver_instance *drvinst = AT_DRVINST(state);
	gn_error error;
	int mode;
	char req[13];

	mode = drvinst->cnmi_mode;
	do {
		snprintf(req, sizeof(req), "AT+CNMI=%d,1\r", mode);
		if (sm_message_send(strlen(req), GN_OP_OnSMS, req, state))
			return GN_ERR_NOTREADY;

		error = sm_block_no_retry(GN_OP_OnSMS, data, state);
	} while (mode-- && error);
	if (error == GN_ERR_NONE) {
		AT_DRVINST(state)->on_sms = data->on_sms;
		AT_DRVINST(state)->sms_callback_data = data->callback_data;
	}
	return error;
}
