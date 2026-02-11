aim_newconn(aim_session_t *sess, int type,
	const char *dest)
{
	aim_conn_t *connstruct;
	fu16_t port = FAIM_LOGIN_PORT;
	char *host;
	int i, ret;

	if (!(connstruct = aim_conn_getnext(sess)))
		return NULL;

	connstruct->sessv = (void *)sess;
	connstruct->type = type;

	if (!dest) {
		connstruct->fd = -1;
		connstruct->status = 0;
		return connstruct;
	}


	for (i = 0; i < (int)strlen(dest); i++) {
		if (dest[i] == ':') {
			port = atoi(&(dest[i + 1]));
			break;
		}
	}

	host = (char *)malloc(i + 1);
	strncpy(host, dest, i);
	host[i] = '\0';

	if ((ret = aim_proxyconnect(sess, host, port, &connstruct->status)) < 0) {
		connstruct->fd = -1;
		connstruct->status = (errno | AIM_CONN_STATUS_CONNERR);
		free(host);
		return connstruct;
	} else
		connstruct->fd = ret;

	free(host);

	return connstruct;
}
