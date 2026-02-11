zmtp1_print(const u_char *cp, u_int len) {
	const u_char *ep = MIN(snapend, cp + len);

	printf(": ZMTP/1.0");
	while (cp < ep)
		cp = zmtp1_print_frame(cp, ep);
}
