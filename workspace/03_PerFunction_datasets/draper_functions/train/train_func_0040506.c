handshake_qtypetest(int dns_fd, int timeout)


{
	char in[4096];
	int read;
	char *s = DOWNCODECCHECK1;
        int slen = DOWNCODECCHECK1_LEN;
	int trycodec;
	int k;

	if (do_qtype == T_NULL)
		trycodec = 'R';
	else
		trycodec = 'T';


	send_downenctest(dns_fd, trycodec, 1, NULL, 0);

	read = handshake_waitdns(dns_fd, in, sizeof(in), 'y', 'Y', timeout);

	if (read != slen)
		return 0;

	for (k = 0; k < slen; k++) {
		if (in[k] != s[k]) {

			return 0;
		}
	}


	return 1;
}
