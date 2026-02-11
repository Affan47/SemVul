enc_read_resp(uint8_t *value, int vlen, uint8_t *pdu, int len)
{
	if (pdu == NULL)
		return 0;


	if (vlen > len - 1)
		vlen = len - 1;

	pdu[0] = ATT_OP_READ_RESP;

	memcpy(pdu + 1, value, vlen);

	return vlen + 1;
}
