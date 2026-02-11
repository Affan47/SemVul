gn_atem_dir_parse(char *buff)
{
	switch (toupper(*buff)) {
		case 'P':
			SMSNumber--;
			gn_atem_sms_handle();
			return;
		case 'N':
			SMSNumber++;
			gn_atem_sms_handle();
			return;
		case 'D':
			data.sms->memory_type = SMSType;
			data.sms->number = SMSNumber;
			if (gn_sm_functions(GN_OP_DeleteSMS, &data, sm) == GN_ERR_NONE) {
				gn_atem_modem_result(MR_OK);
			} else {
				gn_atem_modem_result(MR_ERROR);
			}
			return;
		case 'Q':
			Parser= gn_atem_sms_parse;
			gn_atem_modem_result(MR_OK);
			return;
	}
	gn_atem_modem_result(MR_ERROR);
}
