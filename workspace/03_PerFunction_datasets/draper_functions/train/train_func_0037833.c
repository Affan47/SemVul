list_ax25(void)
{
	int sock, len, offs;
	char buf[512], *b, *s, *digi, *call, *dev, *ct;
	time_t t;

	sock = open_socket();

	wsock(sock, "list ax25\n");

	offs = 0;

	printf("Callsign  Port   Last update         Path\n");


	while (1) {
		len = read(sock, buf + offs, sizeof(buf) - offs - 1);
		if (len <= 0) {
			close(sock);
			return;
		}

		buf[len + offs] = '\0';
		s = buf;
		for (s = buf; (b = strchr(s, '\n')) != NULL; s = b + 1) {
			*b = '\0';

			if (s[0] == '.') {
				close(sock);
				return;
			}

			call = get_next_arg(&s);
			dev = get_next_arg(&s);
			t = strtol(get_next_arg(&s), NULL, 16);

			if (t == 0) {
				ct = "(permanent)";
				ct = strdup(ct);
			} else {
				ct = strdup(ctime(&t));
				ct[strlen(ct) - 6] = '\0';
			}

			printf("%-9s %-6s %s", call, dev, ct);

			free(ct);

			while ((digi = get_next_arg(&s)) != NULL)
				printf(" %s", digi);

			printf("\n");
		}

		if (b == NULL && s != NULL) {
			offs = strlen(s);
			if (offs)
				memcpy(buf, s, offs);
		}
	}

	close(sock);
}
