prestlv_print(register const u_char * pptr, register u_int len,
	      u_int16_t op_msk _U_, int indent)
{
	const struct forces_tlv *tlv = (struct forces_tlv *)pptr;
	register const u_char *tdp = (u_char *) TLV_DATA(tlv);
	struct res_val *r = (struct res_val *)tdp;
	u_int dlen;


	dlen = len - TLV_HDRL;
	if (dlen != RESLEN) {
		printf("illegal RESULT-TLV: %d bytes!\n", dlen);
		return -1;
	}

	TCHECK(*r);
	if (r->result >= 0x18 && r->result <= 0xFE) {
		printf("illegal reserved result code: 0x%x!\n", r->result);
		return -1;
	}

	if (vflag >= 3) {
		char *ib = indent_pr(indent, 0);
		printf("%s  Result: %s (code 0x%x)\n", ib,
		       tok2str(ForCES_errs, NULL, r->result), r->result);
	}
	return 0;

trunc:
	fputs("[|forces]", stdout);
	return -1;
}
