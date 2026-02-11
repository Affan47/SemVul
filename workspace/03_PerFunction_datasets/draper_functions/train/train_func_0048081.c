of10_vendor_data_print(const u_char *cp, const u_char *ep, const u_int len) {
	if (len < 4)
		goto corrupt;

	TCHECK2(*cp, 4);
	printf(", vendor 0x%08x", EXTRACT_32BITS(cp));
	cp += 4;

	return of10_data_print(cp, ep, len - 4);

corrupt:
	printf(" (corrupt)");
	TCHECK2(*cp, len);
	return cp + len;
trunc:
	printf(" [|openflow]");
	return ep;
}
