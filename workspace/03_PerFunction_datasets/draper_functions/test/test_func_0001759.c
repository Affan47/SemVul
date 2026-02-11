sms_encode(const struct sms *in, int *len, int *tpdu_len,
			unsigned char *pdu)
{
	int offset = 0;
	int tpdu_start;

	if (in->type == SMS_TYPE_DELIVER || in->type == SMS_TYPE_SUBMIT ||
			in->type == SMS_TYPE_COMMAND)
		if (!sms_encode_address_field(&in->sc_addr, TRUE, pdu, &offset))
			return FALSE;

	tpdu_start = offset;

	switch (in->type) {
	case SMS_TYPE_DELIVER:
		if (encode_deliver(&in->deliver, pdu, &offset) == FALSE)
			return FALSE;
		break;
	case SMS_TYPE_DELIVER_REPORT_ACK:
		if (!encode_deliver_ack_report(&in->deliver_ack_report, pdu,
						&offset))
			return FALSE;
		break;
	case SMS_TYPE_DELIVER_REPORT_ERROR:
		if (!encode_deliver_err_report(&in->deliver_err_report, pdu,
						&offset))
			return FALSE;
		break;
	case SMS_TYPE_STATUS_REPORT:
		if (!encode_status_report(&in->status_report, pdu, &offset))
			return FALSE;
		break;
	case SMS_TYPE_SUBMIT:
		if (!encode_submit(&in->submit, pdu, &offset))
			return FALSE;
		break;
	case SMS_TYPE_SUBMIT_REPORT_ACK:
		if (!encode_submit_ack_report(&in->submit_ack_report, pdu,
						&offset))
			return FALSE;
		break;
	case SMS_TYPE_SUBMIT_REPORT_ERROR:
		if (!encode_submit_err_report(&in->submit_err_report, pdu,
						&offset))
			return FALSE;
		break;
	case SMS_TYPE_COMMAND:
		if (!encode_command(&in->command, pdu, &offset))
			return FALSE;
		break;
	default:
		return FALSE;
	};

	if (tpdu_len)
		*tpdu_len = offset - tpdu_start;

	if (len)
		*len = offset;

	return TRUE;
}
