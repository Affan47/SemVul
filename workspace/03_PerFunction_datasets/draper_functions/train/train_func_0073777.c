GSM_ReadRingtoneFromSMS(gn_sms *message, gn_ringtone *ringtone)
{
	if (message->udh.udh[0].type == GN_SMS_UDH_Ringtone) {
		return gn_ringtone_unpack(ringtone, message->user_data[0].u.text, message->user_data[0].length);
	} else return GN_ERR_WRONGDATAFORMAT;
}
