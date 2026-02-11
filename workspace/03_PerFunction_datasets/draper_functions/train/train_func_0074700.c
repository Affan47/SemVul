zmtp1_print_datagram(const u_char *cp, const u_int len) {
	const u_char *ep = MIN(snapend, cp + len);

	cp = zmtp1_print_intermediate_part(cp, len);
	while (cp < ep)
		cp = zmtp1_print_frame(cp, ep);
}
