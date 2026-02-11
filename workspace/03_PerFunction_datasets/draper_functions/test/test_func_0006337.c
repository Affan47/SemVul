of10_packet_data_print(const u_char *cp, const u_char *ep, const u_int len) {
	if (len == 0)
		return cp;

	printf("\n\t data (%u octets)", len);
	if (vflag < 3)
		return cp + len;
	TCHECK2(*cp, len);
	vflag -= 3;
	printf(", frame decoding below\n");
	ether_print(gndo, cp, len, snapend - cp, NULL, NULL);
	vflag += 3;
	return cp + len;

trunc:
	printf(" [|openflow]");
	return ep;
}
