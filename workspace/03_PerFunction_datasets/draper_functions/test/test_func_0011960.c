addr_debug_print(int verbose, const ioa_addr *addr, const s08bits* s)
{
	if (verbose) {
		if (!addr) {
			TURN_LOG_FUNC(TURN_LOG_LEVEL_INFO, "%s: EMPTY\n", s);
		} else {
			s08bits addrbuf[INET6_ADDRSTRLEN];
			if (!s)
				s = "";
			if (addr->ss.sa_family == AF_INET) {
				TURN_LOG_FUNC(TURN_LOG_LEVEL_INFO, "IPv4. %s: %s:%d\n", s, inet_ntop(AF_INET,
								&addr->s4.sin_addr, addrbuf, INET6_ADDRSTRLEN),
								nswap16(addr->s4.sin_port));
			} else if (addr->ss.sa_family == AF_INET6) {
				TURN_LOG_FUNC(TURN_LOG_LEVEL_INFO, "IPv6. %s: %s:%d\n", s, inet_ntop(AF_INET6,
								&addr->s6.sin6_addr, addrbuf, INET6_ADDRSTRLEN),
								nswap16(addr->s6.sin6_port));
			} else {
				if (addr_any_no_port(addr)) {
					TURN_LOG_FUNC(
									TURN_LOG_LEVEL_INFO,
									"IP. %s: 0.0.0.0:%d\n",
									s,
									nswap16(addr->s4.sin_port));
				} else {
					TURN_LOG_FUNC(TURN_LOG_LEVEL_INFO, "%s: wrong IP address family: %d\n", s,
									(int) (addr->ss.sa_family));
				}
			}
		}
	}
}
