redirect_print(register const u_char * pptr, register u_int len,
	       u_int16_t op_msk _U_, int indent)
{
	const struct forces_tlv *tlv = (struct forces_tlv *)pptr;
	u_int dlen;
	u_int rlen;
	int invtlv;


	dlen = len - TLV_HDRL;
	if (dlen <= RD_MIN) {
		printf("\n\t\ttruncated Redirect TLV: %d bytes missing! ",
		       RD_MIN - dlen);
		return -1;
	}

	rlen = dlen;
	indent += 1;
	while (rlen != 0) {
		TCHECK(*tlv);
		invtlv = tlv_valid(tlv, rlen);
		if (invtlv)
			break;


		if (EXTRACT_16BITS(&tlv->type) == F_TLV_METD) {
			print_metatlv((u_char *) TLV_DATA(tlv), rlen, 0, indent);
		} else if ((EXTRACT_16BITS(&tlv->type) == F_TLV_REDD)) {
			print_reddata((u_char *) TLV_DATA(tlv), rlen, 0, indent);
		} else {
			printf("Unknown REDIRECT TLV 0x%x len %d\n",
			       EXTRACT_16BITS(&tlv->type), EXTRACT_16BITS(&tlv->length));
		}

		tlv = GO_NXT_TLV(tlv, rlen);
	}

	if (rlen) {
		printf
		    ("\n\t\tMessy Redirect TLV header, type (0x%x)\n\t\texcess of %d Bytes ",
		     EXTRACT_16BITS(&tlv->type), rlen - EXTRACT_16BITS(&tlv->length));
		return -1;
	}

	return 0;

trunc:
	fputs("[|forces]", stdout);
	return -1;
}
