print_queuelen(FILE *f, struct rtattr *tb[IFLA_MAX + 1])
{
	int qlen;

	if (tb[IFLA_TXQLEN])
		qlen = *(int *)RTA_DATA(tb[IFLA_TXQLEN]);
	else {
		struct ifreq ifr;
		int s = socket(AF_INET, SOCK_STREAM, 0);

		if (s < 0)
			return;

		memset(&ifr, 0, sizeof(ifr));
		strcpy(ifr.ifr_name, rta_getattr_str(tb[IFLA_IFNAME]));
		if (ioctl(s, SIOCGIFTXQLEN, &ifr) < 0) {
			fprintf(f, "ioctl(SIOCGIFTXQLEN) failed: %s\n", strerror(errno));
			close(s);
			return;
		}
		close(s);
		qlen = ifr.ifr_qlen;
	}
	if (qlen)
		fprintf(f, "qlen %d", qlen);
}
