execute(struct sockaddr *addr)
{
	static char line[1000];
	int pktlen, len, i;

	if (addr) {
		char addrbuf[256] = "";
		int port = -1;

		if (addr->sa_family == AF_INET) {
			struct sockaddr_in *sin_addr = (void *) addr;
			inet_ntop(addr->sa_family, &sin_addr->sin_addr, addrbuf, sizeof(addrbuf));
			port = ntohs(sin_addr->sin_port);
#ifndef NO_IPV6
		} else if (addr && addr->sa_family == AF_INET6) {
			struct sockaddr_in6 *sin6_addr = (void *) addr;

			char *buf = addrbuf;
			*buf++ = '['; *buf = '\0';
			inet_ntop(AF_INET6, &sin6_addr->sin6_addr, buf, sizeof(addrbuf) - 1);
			strcat(buf, "]");

			port = ntohs(sin6_addr->sin6_port);
#endif
		}
		loginfo("Connection from %s:%d", addrbuf, port);
	}

	alarm(init_timeout ? init_timeout : timeout);
	pktlen = packet_read_line(0, line, sizeof(line));
	alarm(0);

	len = strlen(line);
	if (pktlen != len)
		loginfo("Extended attributes (%d bytes) exist <%.*s>",
			(int) pktlen - len,
			(int) pktlen - len, line + len + 1);
	if (len && line[len-1] == '\n') {
		line[--len] = 0;
		pktlen--;
	}


	interp_clear_table(interp_table, ARRAY_SIZE(interp_table));
	interp_set_entry(interp_table, INTERP_SLOT_PERCENT, "%");

	if (len != pktlen) {
	    parse_extra_args(interp_table, line + len + 1, pktlen - len - 1);
	    fill_in_extra_table_entries(interp_table);
	}

	for (i = 0; i < ARRAY_SIZE(daemon_service); i++) {
		struct daemon_service *s = &(daemon_service[i]);
		int namelen = strlen(s->name);
		if (!prefixcmp(line, "git-") &&
		    !strncmp(s->name, line + 4, namelen) &&
		    line[namelen + 4] == ' ') {


			interp_set_entry(interp_table,
					 INTERP_SLOT_DIR, line + namelen + 5);
			return run_service(interp_table, s);
		}
	}

	logerror("Protocol error: '%s'", line);
	return -1;
}
