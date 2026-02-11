new_isakmp_data_payload(uint8_t type, const void *data, size_t data_length)
{
	struct isakmp_payload *result = xallocc(sizeof(struct isakmp_payload));

	if (type != ISAKMP_PAYLOAD_KE && type != ISAKMP_PAYLOAD_HASH
		&& type != ISAKMP_PAYLOAD_SIG && type != ISAKMP_PAYLOAD_NONCE
		&& type != ISAKMP_PAYLOAD_VID && type != ISAKMP_PAYLOAD_NAT_D
		&& type != ISAKMP_PAYLOAD_NAT_D_OLD)
		abort();
	if (data_length >= 16384)
		abort();

	result->type = type;
	result->u.ke.length = data_length;
	result->u.ke.data = xallocc(data_length);
	memcpy(result->u.ke.data, data, data_length);
	return result;
}
