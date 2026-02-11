execute(void)
{
	static char line[1000];
	int pktlen, len, i;
	char *addr = getenv("REMOTE_ADDR"), *port = getenv("REMOTE_PORT");

	if (addr)
		loginfo("Connection from %s:%s", addr, port);

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

	free(hostname);
	free(canon_hostname);
	free(ip_address);
	free(tcp_port);
	hostname = canon_hostname = ip_address = tcp_port = NULL;

	if (len != pktlen)
		parse_host_arg(line + len + 1, pktlen - len - 1);

	for (i = 0; i < ARRAY_SIZE(daemon_service); i++) {
		struct daemon_service *s = &(daemon_service[i]);
		int namelen = strlen(s->name);
		if (!prefixcmp(line, "git-") &&
		    !strncmp(s->name, line + 4, namelen) &&
		    line[namelen + 4] == ' ') {


			return run_service(line + namelen + 5, s);
		}
	}

	logerror("Protocol error: '%s'", line);
	return -1;
}
