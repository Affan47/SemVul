packet6_len_okay(const char *packet, int len) {
	if (len < 1) {
		return 0;
	}
	if ((packet[0] == DHCPV6_RELAY_FORW) ||
	    (packet[0] == DHCPV6_RELAY_REPL)) {
		if (len >= offsetof(struct dhcpv6_relay_packet, options)) {
			return 1;
		} else {
			return 0;
		}
	} else {
		if (len >= offsetof(struct dhcpv6_packet, options)) {
			return 1;
		} else {
			return 0;
		}
	}
}
