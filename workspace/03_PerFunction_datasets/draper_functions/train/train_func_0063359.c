P3110_IncomingSMSSave(int messagetype, unsigned char *message, int length, gn_data *data, struct gn_statemachine *state)
{
	switch (message[0]) {
	case 0x2a:
		dprintf("SMS save OK (0x%02hhx)\n", message[2]);
		data->raw_sms->number = (int) message[2];
		return GN_ERR_NONE;
	case 0x2b:
		dprintf("SMS send failed (0x%02hhx)\n", message[2]);
		return GN_ERR_FAILED;
	default:
		return GN_ERR_INTERNALERROR;
	}
}
