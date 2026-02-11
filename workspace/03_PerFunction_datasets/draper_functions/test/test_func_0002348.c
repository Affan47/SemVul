NK7110_IncomingProfile(int messagetype, unsigned char *message, int length, gn_data *data, struct gn_statemachine *state)
{
	switch (message[3]) {
	case 0x02:
		if (!data->profile) return GN_ERR_INTERNALERROR;
		switch (message[6]) {
		case 0xff:
			char_unicode_decode(data->profile->name, message + 10, message[9]);
			data->profile->default_name = -1;
			break;
		case 0x00:
			data->profile->keypad_tone = (unsigned char)(message[10] - 1);
			break;
		case 0x01:

			data->profile->lights = message[10];
			break;
		case 0x02:
			switch (message[10]) {
			case 0x00: data->profile->call_alert = GN_PROFILE_CALLALERT_Ringing; break;
			case 0x01: data->profile->call_alert = GN_PROFILE_CALLALERT_Ascending; break;
			case 0x02: data->profile->call_alert = GN_PROFILE_CALLALERT_RingOnce; break;
			case 0x03: data->profile->call_alert = GN_PROFILE_CALLALERT_BeepOnce; break;
			case 0x04: data->profile->call_alert = GN_PROFILE_CALLALERT_CallerGroups; break;
			case 0x05: data->profile->call_alert = GN_PROFILE_CALLALERT_Off; break;
			default: return GN_ERR_UNHANDLEDFRAME; break;
			}
			break;
		case 0x03:

			data->profile->ringtone = message[10];
			break;
		case 0x04:
			data->profile->volume = message[10] + 6;
			break;
		case 0x05:
			data->profile->message_tone = message[10];
			break;
		case 0x06:
			data->profile->vibration = message[10];
			break;
		case 0x07:
			data->profile->warning_tone = message[10] ? GN_PROFILE_WARNING_On : GN_PROFILE_WARNING_Off;
			break;
		case 0x08:
			data->profile->caller_groups = message[10];
			break;
		case 0x09:
			data->profile->automatic_answer = message[10];
			break;
		default:
			return GN_ERR_UNHANDLEDFRAME;
			break;
		}
		break;
	default:
		dprintf("Unknown subtype of type 0x39 (%d)\n", message[3]);
		return GN_ERR_UNHANDLEDFRAME;
		break;
	}
	return GN_ERR_NONE;
}
