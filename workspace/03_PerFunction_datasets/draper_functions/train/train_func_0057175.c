sms_concat_header_encode(gn_sms_raw *rawsms, int curr, int total)
{
	char *header = sms_udh_encode(rawsms, GN_SMS_UDH_ConcatenatedMessages);
	if (!header) return GN_ERR_NOTSUPPORTED;
	header[2] = 0xce;
	header[3] = total;
	header[4] = curr;
	return GN_ERR_NONE;
}
