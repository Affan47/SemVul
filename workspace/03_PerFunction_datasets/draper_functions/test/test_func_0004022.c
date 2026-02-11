prot_reply_print(register const u_char *bp, int length, int32_t opcode)
{
	struct rx_header *rxh;
	unsigned long i;

	if (length < (int)sizeof(struct rx_header))
		return;

	rxh = (struct rx_header *) bp;


	printf(" pt");

	if (is_ubik(opcode)) {
		ubik_reply_print(bp, length, opcode);
		return;
	}

	printf(" reply %s", tok2str(pt_req, "op#%d", opcode));

	bp += sizeof(struct rx_header);


	if (rxh->type == RX_PACKET_TYPE_DATA)
		switch (opcode) {
		case 504:
		{
			unsigned long j;
			printf(" ids:");
			TCHECK2(bp[0], 4);
			i = EXTRACT_32BITS(bp);
			bp += sizeof(int32_t);
			for (j = 0; j < i; j++)
				INTOUT();
			if (j == 0)
				printf(" <none!>");
		}
			break;
		case 505:
		{
			unsigned long j;
			TCHECK2(bp[0], 4);
			j = EXTRACT_32BITS(bp);
			bp += sizeof(int32_t);


			for (i = 0; i < j; i++) {
				VECOUT(PRNAMEMAX);
			}
			if (j == 0)
				printf(" <none!>");
		}
			break;
		case 508:
		case 514:
		case 517:
		case 518:
		case 519:
		{
			unsigned long j;
			TCHECK2(bp[0], 4);
			j = EXTRACT_32BITS(bp);
			bp += sizeof(int32_t);
			for (i = 0; i < j; i++) {
				INTOUT();
			}
			if (j == 0)
				printf(" <none!>");
		}
			break;
		case 510:
			printf(" maxuid");
			INTOUT();
			printf(" maxgid");
			INTOUT();
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
	printf(" [|pt]");
}
