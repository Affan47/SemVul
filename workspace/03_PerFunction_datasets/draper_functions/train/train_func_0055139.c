decode_deliver_report(const unsigned char *pdu, int len,
					struct sms *out)
{
	int offset = 0;
	unsigned char octet;
	gboolean udhi;
	guint8 uninitialized_var(fcs);
	guint8 pi;
	guint8 pid = 0;
	guint8 dcs = 0;
	guint8 udl = 0;

	if (!next_octet(pdu, len, &offset, &octet))
		return FALSE;

	udhi = is_bit_set(octet, 6);

	if (!next_octet(pdu, len, &offset, &octet))
		return FALSE;


	if (octet >= 0x80) {
		out->type = SMS_TYPE_DELIVER_REPORT_ERROR;
		fcs = octet;

		if (!next_octet(pdu, len, &offset, &octet))
			return FALSE;
	} else
		out->type = SMS_TYPE_DELIVER_REPORT_ACK;

	pi = octet & 0x07;

	if (pi & 0x01) {
		if (!next_octet(pdu, len, &offset, &pid))
			return FALSE;
	}

	if (pi & 0x02) {
		if (!next_octet(pdu, len, &offset, &dcs))
			return FALSE;
	}

	if (out->type == SMS_TYPE_DELIVER_REPORT_ERROR) {
		out->deliver_err_report.udhi = udhi;
		out->deliver_err_report.fcs = fcs;
		out->deliver_err_report.pi = pi;
		out->deliver_err_report.pid = pid;
		out->deliver_err_report.dcs = dcs;
	} else {
		out->deliver_ack_report.udhi = udhi;
		out->deliver_ack_report.pi = pi;
		out->deliver_ack_report.pid = pid;
		out->deliver_ack_report.dcs = dcs;
	}

	if (pi & 0x04) {
		int expected;

		if (!next_octet(pdu, len, &offset, &udl))
			return FALSE;

		expected = sms_udl_in_bytes(udl, dcs);

		if ((len - offset) < expected)
			return FALSE;

		if (out->type == SMS_TYPE_DELIVER_REPORT_ERROR) {
			out->deliver_err_report.udl = udl;
			memcpy(out->deliver_err_report.ud,
					pdu+offset, expected);
		} else {
			out->deliver_ack_report.udl = udl;
			memcpy(out->deliver_ack_report.ud,
					pdu+offset, expected);
		}
	}

	return TRUE;
}
