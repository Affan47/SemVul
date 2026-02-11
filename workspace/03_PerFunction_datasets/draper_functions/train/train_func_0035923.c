cbs_encode(const struct cbs *cbs, int *len, unsigned char *pdu)
{
	pdu[0] = (cbs->gs << 6) | ((cbs->message_code >> 4) & 0x3f);
	pdu[1] = ((cbs->message_code & 0xf) << 4) | cbs->update_number;
	pdu[2] = cbs->message_identifier >> 8;
	pdu[3] = cbs->message_identifier & 0xff;
	pdu[4] = cbs->dcs;
	pdu[5] = cbs->max_pages | (cbs->page << 4);

	memcpy(pdu + 6, cbs->ud, 82);

	if (len)
		*len = 88;

	return TRUE;
}
