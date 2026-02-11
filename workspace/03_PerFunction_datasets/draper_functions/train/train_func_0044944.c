setup_client_connect(int *did_client_connect) {
	if (client_connect != NULL) {
		char *remainder = NULL;
		if (inetd) {
			rfbLog("wait_for_client: -connect disallowed in inetd mode: %s\n",
			    client_connect);
		} else if (screen && screen->clientHead) {
			rfbLog("wait_for_client: -connect disallowed: client exists: %s\n",
			    client_connect);
		} else if (strchr(client_connect, '=')) {
			rfbLog("wait_for_client: invalid -connect string: %s\n",
			    client_connect);
		} else {
			char *q = strchr(client_connect, ',');
			if (q) {
				rfbLog("wait_for_client: only using first"
				    " connect host in: %s\n", client_connect);
				remainder = strdup(q+1);
				*q = '\0';
			}
			rfbLog("wait_for_client: reverse_connect(%s)\n",
			    client_connect);
			reverse_connect(client_connect);
			*did_client_connect = 1;
		}
		free(client_connect);
		if (remainder != NULL) {

			client_connect = remainder;
		} else {
			client_connect = NULL;
		}
	}
}
