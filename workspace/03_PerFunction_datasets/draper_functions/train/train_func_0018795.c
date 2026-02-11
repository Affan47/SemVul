NK7110_IncomingClock(int messagetype, unsigned char *message, int length, gn_data *data, struct gn_statemachine *state)
{
	gn_error e = GN_ERR_NONE;

	if (!data) return GN_ERR_INTERNALERROR;
	switch (message[3]) {
	case NK7110_SUBCLO_DATE_RCVD:
		if (!data->datetime) return GN_ERR_INTERNALERROR;
		data->datetime->year = (((unsigned int)message[8]) << 8) + message[9];
		data->datetime->month = message[10];
		data->datetime->day = message[11];
		data->datetime->hour = message[12];
		data->datetime->minute = message[13];
		data->datetime->second = message[14];

		break;
	case NK7110_SUBCLO_DATE_SET:
		break;
	case NK7110_SUBCLO_ALARM_RCVD:
		if (!data->alarm) return GN_ERR_INTERNALERROR;
		switch(message[8]) {
		case NK7110_ALARM_ENABLED:
			data->alarm->enabled = true;
			break;
		case NK7110_ALARM_DISABLED:
			data->alarm->enabled = false;
			break;
		default:
			data->alarm->enabled = false;
			dprintf("Unknown value of alarm enable byte: 0x%02x\n", message[8]);
			e = GN_ERR_UNKNOWN;
			break;
		}

		data->alarm->timestamp.hour = message[9];
		data->alarm->timestamp.minute = message[10];

		break;
	case NK7110_SUBCLO_ALARM_SET:
		break;
	default:
		dprintf("Unknown subtype of type 0x%02x (clock handling): 0x%02x\n", NK7110_MSG_CLOCK, message[3]);
		e = GN_ERR_UNHANDLEDFRAME;
		break;
	}
	return e;
}
