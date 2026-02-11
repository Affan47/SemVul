usm_print(const u_char *np, u_int length)
{
        struct be elem;
	int count = 0;


	if ((count = asn1_parse(np, length, &elem)) < 0)
		return;
	if (elem.type != BE_SEQ) {
		fputs("[!usm]", stdout);
		asn1_print(&elem);
		return;
	}
	length = elem.asnlen;
	np = (u_char *)elem.data.raw;


	if ((count = asn1_parse(np, length, &elem)) < 0)
		return;
	if (elem.type != BE_STR) {
		fputs("[msgAuthoritativeEngineID!=STR]", stdout);
		asn1_print(&elem);
		return;
	}
	length -= count;
	np += count;


	if ((count = asn1_parse(np, length, &elem)) < 0)
		return;
	if (elem.type != BE_INT) {
		fputs("[msgAuthoritativeEngineBoots!=INT]", stdout);
		asn1_print(&elem);
		return;
	}
	if (vflag)
	        printf("B=%d ", elem.data.integer);
	length -= count;
	np += count;


	if ((count = asn1_parse(np, length, &elem)) < 0)
		return;
	if (elem.type != BE_INT) {
		fputs("[msgAuthoritativeEngineTime!=INT]", stdout);
		asn1_print(&elem);
		return;
	}
	if (vflag)
	        printf("T=%d ", elem.data.integer);
	length -= count;
	np += count;


	if ((count = asn1_parse(np, length, &elem)) < 0)
		return;
	if (elem.type != BE_STR) {
		fputs("[msgUserName!=STR]", stdout);
		asn1_print(&elem);
		return;
	}
	length -= count;
        np += count;

	printf("U=%.*s ", (int)elem.asnlen, elem.data.str);


	if ((count = asn1_parse(np, length, &elem)) < 0)
		return;
	if (elem.type != BE_STR) {
		fputs("[msgAuthenticationParameters!=STR]", stdout);
		asn1_print(&elem);
		return;
	}
	length -= count;
        np += count;


	if ((count = asn1_parse(np, length, &elem)) < 0)
		return;
	if (elem.type != BE_STR) {
		fputs("[msgPrivacyParameters!=STR]", stdout);
		asn1_print(&elem);
		return;
	}
	length -= count;
        np += count;

	if ((u_int)count < length)
		printf("[%d extra after usm SEQ]", length - count);
}
