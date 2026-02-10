htc_process_trailer(struct htc_target *target, u8 *buffer,
			       int len, enum htc_endpoint_id from_ep)
{
	struct htc_credit_report *report;
	struct htc_record_hdr *record;
	u8 *record_buf, *orig_buf;
	int orig_len, status;

	orig_buf = buffer;
	orig_len = len;
	status = 0;

	while (len > 0) {
		if (len < sizeof(struct htc_record_hdr)) {
			status = -EINVAL;
			break;
		}


		record = (struct htc_record_hdr *) buffer;
		len -= sizeof(struct htc_record_hdr);
		buffer += sizeof(struct htc_record_hdr);

		if (record->len > len) {

			ath6kl_dbg(ATH6KL_DBG_HTC,
				   "invalid length: %d (id:%d) buffer has: %d bytes left\n",
				   record->len, record->rec_id, len);
			status = -EINVAL;
			break;
		}


		record_buf = buffer;

		switch (record->rec_id) {
		case HTC_RECORD_CREDITS:
			if (record->len < sizeof(struct htc_credit_report)) {
				WARN_ON_ONCE(1);
				return -EINVAL;
			}

			report = (struct htc_credit_report *) record_buf;
			htc_process_credit_report(target, report,
						  record->len / sizeof(*report),
						  from_ep);
			break;
		default:
			ath6kl_dbg(ATH6KL_DBG_HTC,
				   "unhandled record: id:%d length:%d\n",
				   record->rec_id, record->len);
			break;
		}

		if (status != 0)
			break;


		buffer += record->len;
		len -= record->len;
	}

	return status;
}
