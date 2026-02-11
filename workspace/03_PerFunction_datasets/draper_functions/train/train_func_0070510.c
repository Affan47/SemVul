statcmd(void)
{
	struct sockaddr *sn;
	char ipaddr[INET6_ADDRSTRLEN];

	lreply(211, "%s FTP server status:", hostname, version);
	printf("     %s\r\n", version);
	printf("     Connected to %s", remotehost);
	if (!isdigit(remotehost[0])) {
		(void) getnameinfo((struct sockaddr *) &his_addr,
				sizeof(struct sockaddr_storage),
				ipaddr, sizeof(ipaddr), NULL, 0,
				NI_NUMERICHOST);
		printf(" (%s)", ipaddr);
	}
	printf("\r\n");
	if (logged_in) {
		if (guest)
			printf("     Logged in anonymously\r\n");
		else
			printf("     Logged in as %s\r\n", pw->pw_name);
	} else if (askpasswd)
		printf("     Waiting for password\r\n");
	else
		printf("     Waiting for user name\r\n");
	printf("     TYPE: %s", typenames[type]);
	if (type == TYPE_A || type == TYPE_E)
		printf(", FORM: %s", formnames[form]);
	if (type == TYPE_L)
#if CHAR_BIT == 8
		printf(" %d", CHAR_BIT);
#else
		printf(" %d", bytesize);
#endif
	printf("; STRUcture: %s; transfer MODE: %s\r\n",
	    strunames[stru], modenames[mode]);
	if (data != -1)
		printf("     Data connection open\r\n");
	else if (pdata != -1) {
		printf("     in Passive mode");
		sn = (struct sockaddr *) &pasv_addr;
		goto printaddr;
	} else if (usedefault == 0) {
		printf("     PORT");
		sn = (struct sockaddr *) &data_dest;
printaddr:
#define UC(b) (((int) b) & 0xff)
		if (sn->sa_family == AF_INET6)
			printf(" (|||%d|)\r\n", get_port(sn));
		else {
			uint32_t ip4ad = get_ipv4address(sn);
			in_port_t port = get_port(sn);

			printf(" (%d,%d,%d,%d,%d,%d)\r\n",
				UC(ip4ad >> 24), UC(ip4ad >> 16),
				UC(ip4ad >> 8), UC(ip4ad),
				UC(port >> 8), UC(port));
		}
#undef UC
	} else
		printf("     No data connection\r\n");
	reply(211, "End of status");
}
