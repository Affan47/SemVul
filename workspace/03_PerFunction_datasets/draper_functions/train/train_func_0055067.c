sms_header_encode(gn_data *data, struct gn_statemachine *state, unsigned char *req, int ulength, bool save_sms)
{
	int pos = 0;
	unsigned char smsc[256], remote[256];


	data->raw_sms->remote_number[0] = (data->raw_sms->remote_number[0] + 1) / 2 + 1;


	snprintf(smsc, sizeof(smsc), "%s", char_bcd_number_get(data->raw_sms->message_center));
	snprintf(remote, sizeof(remote), "%s", char_bcd_number_get(data->raw_sms->remote_number));

	dprintf("smsc:'%s' remote:'%s'\n", smsc, remote);

	if (save_sms) {
		req[pos++] = get_memory_type(data->raw_sms->memory_type);
		req[pos++] = data->raw_sms->status;
		req[pos++] = 0x01;
	} else {

		if (data->raw_sms->type != GN_SMS_MT_Deliver)
			req[pos] = 0x01;
		else
			req[pos] = 0x00;
		if (data->raw_sms->reply_via_same_smsc)  req[pos] |= 0x80;
		if (data->raw_sms->reject_duplicates)    req[pos] |= 0x04;
		if (data->raw_sms->report)               req[pos] |= 0x20;
		if (data->raw_sms->udh_indicator)        req[pos] |= 0x40;
		if (data->raw_sms->type != GN_SMS_MT_Deliver) {
			switch (data->raw_sms->validity_indicator) {
			case GN_SMS_VP_None: default:   break;
			case GN_SMS_VP_RelativeFormat:  req[pos] |= 0x10; break;
			case GN_SMS_VP_AbsoluteFormat:  req[pos] |= 0x18; break;
			case GN_SMS_VP_EnhancedFormat:  req[pos] |= 0x08; break;
			}
		}
		dprintf("First Octet: %02x\n", req[pos]);
		pos++;
	}

	req[pos++] = data->raw_sms->pid;
	req[pos++] = data->raw_sms->dcs;


	memcpy(req + pos, data->raw_sms->validity, 7);
	pos += 7;

	req[pos++] = ulength;


	req[pos++] = strlen(smsc);
	memcpy(req + pos, smsc, strlen(smsc));
	pos += strlen(smsc);
	req[pos++] = strlen(remote);
	memcpy(req + pos, remote, strlen(remote));
	pos += strlen(remote);


	if (save_sms)
		req[pos++] = data->raw_sms->remote_number[1];

	return pos;
}
