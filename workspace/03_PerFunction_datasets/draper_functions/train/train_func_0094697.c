tn3270e_nak(enum pds rv)
{
	unsigned char rsp_buf[10];
	tn3270e_header *h_in = (tn3270e_header *)ibuf;
	int rsp_len = 0;
	char *neg = NULL;

	rsp_buf[rsp_len++] = TN3270E_DT_RESPONSE;
	rsp_buf[rsp_len++] = 0;
	rsp_buf[rsp_len++] = TN3270E_RSF_NEGATIVE_RESPONSE;
	rsp_buf[rsp_len++] = h_in->seq_number[0];
	if (h_in->seq_number[0] == IAC)
		rsp_buf[rsp_len++] = IAC;
	rsp_buf[rsp_len++] = h_in->seq_number[1];
	if (h_in->seq_number[1] == IAC)
		rsp_buf[rsp_len++] = IAC;
	switch (rv) {
	default:
	case PDS_BAD_CMD:
		rsp_buf[rsp_len++] = TN3270E_NEG_COMMAND_REJECT;
		neg = "COMMAND-REJECT";
		break;
	case PDS_BAD_ADDR:
		rsp_buf[rsp_len++] = TN3270E_NEG_OPERATION_CHECK;
		neg = "OPERATION-CHECK";
		break;
	}
	rsp_buf[rsp_len++] = IAC;
	rsp_buf[rsp_len++] = EOR;
	trace_dsn("SENT TN3270E(RESPONSE NEGATIVE-RESPONSE %u) %s\n",
		h_in->seq_number[0] << 8 | h_in->seq_number[1], neg);
	net_rawout(rsp_buf, rsp_len);
}
