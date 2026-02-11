AT_CallDivert(gn_data *data, struct gn_statemachine *state)
{
	char req[64];
	int ctype;

	if (!data->call_divert)
		return GN_ERR_UNKNOWN;

	switch (data->call_divert->ctype) {
	case GN_CDV_VoiceCalls:
		ctype = 1;
		break;
	case GN_CDV_FaxCalls:
		ctype = 2;
		break;
	case GN_CDV_DataCalls:
		ctype = 4;
		break;
	default:
		ctype = 7;
		break;
	}

	if (data->call_divert->operation == GN_CDV_Register) {


		if (data->call_divert->timeout)
			snprintf(req, sizeof(req), "AT+CCFC=%d,%d,\"%s\",%d,%d,,,%d\r",
				 data->call_divert->type,
				 data->call_divert->operation,
				 data->call_divert->number.number,
				 data->call_divert->number.type,
				 ctype, data->call_divert->timeout);
		else
			snprintf(req, sizeof(req), "AT+CCFC=%d,%d,\"%s\",%d,%d\r",
				 data->call_divert->type,
				 data->call_divert->operation,
				 data->call_divert->number.number,
				 data->call_divert->number.type,
				 ctype);
	} else {
		snprintf(req, sizeof(req), "AT+CCFC=%d,%d\r",
				data->call_divert->type,
				data->call_divert->operation);
	}

	if (sm_message_send(strlen(req), GN_OP_CallDivert, req, state))
		return GN_ERR_NOTREADY;

	return sm_block_no_retry_timeout(GN_OP_CallDivert, 2000, data, state);
}
