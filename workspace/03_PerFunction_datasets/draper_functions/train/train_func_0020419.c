avctp_send(struct avctp *session, uint8_t transaction, uint8_t cr,
				uint8_t code, uint8_t subunit, uint8_t opcode,
				uint8_t *operands, size_t operand_count)
{
	uint8_t *buf;
	struct avctp_header *avctp;
	struct avc_header *avc;
	uint8_t *pdu;
	int sk, err = 0;
	uint16_t size;

	if (session->state != AVCTP_STATE_CONNECTED)
		return -ENOTCONN;

	sk = g_io_channel_unix_get_fd(session->io);
	size = AVCTP_HEADER_LENGTH + AVC_HEADER_LENGTH + operand_count;
	buf = g_malloc0(size);

	avctp = (void *) buf;
	avc = (void *) &buf[AVCTP_HEADER_LENGTH];
	pdu = (void *) &buf[AVCTP_HEADER_LENGTH + AVC_HEADER_LENGTH];

	avctp->transaction = transaction;
	avctp->packet_type = AVCTP_PACKET_SINGLE;
	avctp->cr = cr;
	avctp->pid = htons(AV_REMOTE_SVCLASS_ID);

	avc->code = code;
	avc->subunit_type = subunit;
	avc->opcode = opcode;

	memcpy(pdu, operands, operand_count);

	if (write(sk, buf, size) < 0)
		err = -errno;

	g_free(buf);
	return err;
}
