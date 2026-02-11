ubik_print(register const u_char *bp)
{
	int ubik_op;
	int32_t temp;


	ubik_op = EXTRACT_32BITS(bp + sizeof(struct rx_header));

	printf(" ubik call %s", tok2str(ubik_req, "op#%d", ubik_op));


	bp += sizeof(struct rx_header) + 4;

	switch (ubik_op) {
		case 10000:
			TCHECK2(bp[0], 4);
			temp = EXTRACT_32BITS(bp);
			bp += sizeof(int32_t);
			printf(" syncsite %s", temp ? "yes" : "no");
			printf(" votestart");
			DATEOUT();
			printf(" dbversion");
			UBIK_VERSIONOUT();
			printf(" tid");
			UBIK_VERSIONOUT();
			break;
		case 10003:
			printf(" site");
			UINTOUT();
			break;
		case 20000:
		case 20001:
		case 20007:
		case 20008:
		case 20010:
			printf(" tid");
			UBIK_VERSIONOUT();
			break;
		case 20002:
			printf(" tid");
			UBIK_VERSIONOUT();
			printf(" file");
			INTOUT();
			printf(" pos");
			INTOUT();
			printf(" length");
			INTOUT();
			temp = EXTRACT_32BITS(bp);
			bp += sizeof(int32_t);
			tok2str(ubik_lock_types, "type %d", temp);
			break;
		case 20003:
			printf(" tid");
			UBIK_VERSIONOUT();
			printf(" file");
			INTOUT();
			printf(" pos");
			INTOUT();
			break;
		case 20005:
			printf(" file");
			INTOUT();
			break;
		case 20006:
			printf(" file");
			INTOUT();
			printf(" length");
			INTOUT();
			printf(" dbversion");
			UBIK_VERSIONOUT();
			break;
		case 20009:
			printf(" tid");
			UBIK_VERSIONOUT();
			printf(" file");
			INTOUT();
			printf(" length");
			INTOUT();
			break;
		case 20012:
			printf(" tid");
			UBIK_VERSIONOUT();
			printf(" oldversion");
			UBIK_VERSIONOUT();
			printf(" newversion");
			UBIK_VERSIONOUT();
			break;
		default:
			;
	}

	return;

trunc:
	printf(" [|ubik]");
}
