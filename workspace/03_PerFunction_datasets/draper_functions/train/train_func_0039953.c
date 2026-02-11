ReplySendSMS(int messagetype, unsigned char *buffer, int length, gn_data *data, struct gn_statemachine *state)
{
	at_line_buffer buf;
	gn_error error;

	if ((error = at_error_get(buffer, state)) != GN_ERR_NONE) return error;

	buf.line1 = buffer + 1;
	buf.length = length;
	splitlines(&buf);

	if (!strncmp("+CMGW:", buf.line2, 6)) {

		data->raw_sms->number = atoi(buf.line2 + 6);
		dprintf("Message saved (location: %d)\n", data->raw_sms->number);
	} else if (!strncmp("+CMGS:", buf.line2, 6)) {

		data->raw_sms->reference = atoi(buf.line2 + 6);
		dprintf("Message sent (reference: %d)\n", data->raw_sms->reference);
	} else {
		data->raw_sms->reference = -1;
	}
	return GN_ERR_NONE;
}
