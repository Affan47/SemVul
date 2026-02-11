cb_reply_print(register const u_char *bp, int length, int32_t opcode)
{
	struct rx_header *rxh;

	if (length <= (int)sizeof(struct rx_header))
		return;

	rxh = (struct rx_header *) bp;


	printf(" cb reply %s", tok2str(cb_req, "op#%d", opcode));

	bp += sizeof(struct rx_header);


	if (rxh->type == RX_PACKET_TYPE_DATA)
		switch (opcode) {
		case 213:
			AFSUUIDOUT();
			break;
		default:
		;
		}
	else {


		printf(" errcode");
		INTOUT();
	}

	return;

trunc:
	printf(" [|cb]");
}
