sdatailv_print(register const u_char * pptr, register u_int len,
	       u_int16_t op_msk _U_, int indent)
{
	u_int rlen;
	const struct forces_ilv *ilv = (struct forces_ilv *)pptr;
	int invilv;

	if (len < ILV_HDRL) {
		printf("Error: BAD SPARSEDATA-TLV!\n");
		return -1;
	}
	rlen = len;
	indent += 1;
	while (rlen != 0) {
#if 0
		printf("Jamal - outstanding length <%d>\n", rlen);
#endif
		char *ib = indent_pr(indent, 1);
		register const u_char *tdp = (u_char *) ILV_DATA(ilv);
		TCHECK(*ilv);
		invilv = ilv_valid(ilv, rlen);
		if (invilv) {
			printf("%s[", &ib[1]);
			hex_print_with_offset(ib, tdp, rlen, 0);
			printf("\n%s]\n", &ib[1]);
			return -1;
		}
		if (vflag >= 3) {
			int ilvl = EXTRACT_32BITS(&ilv->length);
			printf("\n%s ILV: type %x length %d\n", &ib[1],
			       EXTRACT_32BITS(&ilv->type), ilvl);
			hex_print_with_offset("\t\t[", tdp, ilvl-ILV_HDRL, 0);
		}

		ilv = GO_NXT_ILV(ilv, rlen);
	}

	return 0;

trunc:
	fputs("[|forces]", stdout);
	return -1;
}
