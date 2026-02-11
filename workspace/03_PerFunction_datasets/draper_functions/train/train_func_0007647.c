dpd_add_vendor_payload(struct message *msg)
{
	u_int8_t *buf;
	size_t buflen = sizeof dpd_vendor_id + ISAKMP_GEN_SZ;

	buf = malloc(buflen);
	if (!buf) {
		log_error("dpd_add_vendor_payload: malloc(%lu) failed",
		    (unsigned long)buflen);
		return -1;
	}

	SET_ISAKMP_GEN_LENGTH(buf, buflen);
	memcpy(buf + ISAKMP_VENDOR_ID_OFF, dpd_vendor_id,
	    sizeof dpd_vendor_id);
	if (message_add_payload(msg, ISAKMP_PAYLOAD_VENDOR, buf, buflen, 1)) {
		free(buf);
		return -1;
	}

	return 0;
}
