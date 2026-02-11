gn_atem_sms_print(char *line, gn_sms *message, int mode)
{
	switch (mode) {
	case INTERACT_MODE:
		gsprintf(line, MAX_LINE_LENGTH,
			_("\r\nDate/time: %d/%d/%d %d:%02d:%02d Sender: %s Msg Center: %s\r\nText: %s\r\n"),
			message->smsc_time.day, message->smsc_time.month, message->smsc_time.year,
			message->smsc_time.hour, message->smsc_time.minute, message->smsc_time.second,
			message->remote.number, message->smsc.number, message->user_data[0].u.text);
		break;
	case TEXT_MODE:
		if ((message->dcs.type == GN_SMS_DCS_GeneralDataCoding) &&
		    (message->dcs.u.general.alphabet == GN_SMS_DCS_8bit))
			gsprintf(line, MAX_LINE_LENGTH,
				_("\"%s\",\"%s\",,\"%02d/%02d/%02d,%02d:%02d:%02d+%02d\"\r\n%s"),
				(message->status ? _("REC READ") : _("REC UNREAD")),
				message->remote.number,
				message->smsc_time.year, message->smsc_time.month, message->smsc_time.day,
				message->smsc_time.hour, message->smsc_time.minute, message->smsc_time.second,
				message->time.timezone, _("<Not implemented>"));
		else
			gsprintf(line, MAX_LINE_LENGTH,
				_("\"%s\",\"%s\",,\"%02d/%02d/%02d,%02d:%02d:%02d+%02d\"\r\n%s"),
				(message->status ? _("REC READ") : _("REC UNREAD")),
				message->remote.number,
				message->smsc_time.year, message->smsc_time.month, message->smsc_time.day,
				message->smsc_time.hour, message->smsc_time.minute, message->smsc_time.second,
				message->time.timezone, message->user_data[0].u.text);
		break;
	case PDU_MODE:
		gsprintf(line, MAX_LINE_LENGTH, _("0,<Not implemented>"));
		break;
	default:
		gsprintf(line, MAX_LINE_LENGTH, _("<Unknown mode>"));
		break;
	}
}
