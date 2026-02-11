dec_find_by_type_req(const uint8_t *pdu, int len, uint16_t *start,
		uint16_t *end, bt_uuid_t *uuid, uint8_t *value, int *vlen)
{
	int valuelen;
	uint16_t min_len = sizeof(pdu[0]) + sizeof(*start) +
						sizeof(*end) + sizeof(uint16_t);

	if (pdu == NULL)
		return 0;

	if (len < min_len)
		return 0;

	if (pdu[0] != ATT_OP_FIND_BY_TYPE_REQ)
		return 0;


	if (start)
		*start = att_get_u16(&pdu[1]);


	if (end)
		*end = att_get_u16(&pdu[3]);


	if (uuid)
		*uuid = att_get_uuid16(&pdu[5]);

	valuelen = len - min_len;


	if (valuelen > 0 && value)
		memcpy(value, pdu + min_len, valuelen);

	if (vlen)
		*vlen = valuelen;

	return len;
}
