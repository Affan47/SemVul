sms_pdu_decode(gn_sms_raw *rawsms, gn_sms *sms)
{
	unsigned int size = 0;
	gn_error error;

	error = sms_header_decode(rawsms, sms, &sms->udh);
	ERROR();
	sms->user_data[0].dr_status = GN_SMS_DR_Status_None;
	switch (sms->type) {
	case GN_SMS_MT_DeliveryReport:
	case GN_SMS_MT_StatusReport:
		sms_status(rawsms->report_status, sms);
		break;
	case GN_SMS_MT_PictureTemplate:
	case GN_SMS_MT_Picture:


		sms->udh.number = 1;
		sms->udh.udh[0].type = GN_SMS_UDH_MultipartMessage;
		if ((rawsms->user_data[0] == 0x48) && (rawsms->user_data[1] == 0x1c)) {

			dprintf("First picture then text!\n");


			sms->user_data[0].type = GN_SMS_DATA_Bitmap;
			gn_bmp_sms_read(GN_BMP_PictureMessage, rawsms->user_data,
					NULL, &sms->user_data[0].u.bitmap);
#ifdef DEBUG
			gn_bmp_print(&sms->user_data[0].u.bitmap, stderr);
#endif
			size = rawsms->user_data_length - 4 - sms->user_data[0].u.bitmap.size;

			sms->user_data[1].type = GN_SMS_DATA_NokiaText;
			sms_data_decode(rawsms->user_data + 5 + sms->user_data[0].u.bitmap.size,
					(unsigned char *)&(sms->user_data[1].u.text),
					rawsms->length - sms->user_data[0].u.bitmap.size - 4,
					size, 0, sms->dcs);
		} else {

			dprintf("First text then picture!\n");


			sms->user_data[1].type = GN_SMS_DATA_NokiaText;
			sms_data_decode(rawsms->user_data + 3,
					(unsigned char *)&(sms->user_data[1].u.text),
					rawsms->user_data[1], rawsms->user_data[0], 0, sms->dcs);


			sms->user_data[0].type = GN_SMS_DATA_Bitmap;
			gn_bmp_sms_read(GN_BMP_PictureMessage,
					rawsms->user_data + rawsms->user_data[0] + 7,
					NULL, &sms->user_data[0].u.bitmap);
#ifdef DEBUG
			gn_bmp_print(&sms->user_data[0].u.bitmap, stderr);
#endif
		}
		break;

	default:
		return sms_data_decode(rawsms->user_data + sms->udh.length,
				(unsigned char *)&sms->user_data[0].u.text,
				rawsms->length,
				rawsms->user_data_length,
				sms->udh.length,
				sms->dcs);
		break;
	}

	return GN_ERR_NONE;
}
