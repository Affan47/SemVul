target_redirected(struct iscsi_target *target,
	struct iscsi_connection *conn, char *buf, int *reason)
{
	struct sockaddr_storage from;
	struct addrinfo hints, *res;
	socklen_t len;
	int ret, rsn = 0;
	char *p, *q, *str, *port = NULL, *addr;
	char buffer[NI_MAXHOST + NI_MAXSERV + 4];
	char dst[INET6_ADDRSTRLEN], in_buf[1024];

	len = sizeof(from);
	ret = conn->tp->ep_getpeername(conn, (struct sockaddr *)&from, &len);
	if (ret < 0)
		return 0;

	ret = 1;
	if (target->redirect_info.callback) {
		p = in_buf;
		p += sprintf(p, "%s ", target->redirect_info.callback);
		p += sprintf(p, "%s ", tgt_targetname(target->tid));
		ret = getnameinfo((struct sockaddr *)&from, sizeof(from), dst,
				sizeof(dst), NULL, 0, NI_NUMERICHOST);
		if (ret)
			goto predefined;
		sprintf(p, "%s", dst);
		ret = get_redirect_address(in_buf, buffer,
					sizeof(buffer), &addr, &port, &rsn);
		if (ret)
			return -1;
	}

predefined:
	if (ret) {
		if (!strlen(target->redirect_info.addr))
			return 0;

		addr = target->redirect_info.addr;
		port = target->redirect_info.port;
		rsn = target->redirect_info.reason;
	}

	if (rsn != ISCSI_LOGIN_STATUS_TGT_MOVED_TEMP &&
	    rsn != ISCSI_LOGIN_STATUS_TGT_MOVED_PERM)
		return 0;

	p = strdup(addr);
	if (!p)
		return 0;
	str = p;

	if (*p == '[') {
		p++;
		if (!(q = strchr(p, ']'))) {
			free(str);
			return 0;
		}
		*(q++) = '\0';
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_NUMERICHOST;

	ret = getaddrinfo(p, NULL, &hints, &res);
	if (ret < 0) {
		free(str);
		return 0;
	}

	ret = address_match(res->ai_addr, (struct sockaddr *)&from);
	freeaddrinfo(res);
	free(str);

	if (!ret) {
		sprintf(buf, "%s:%s", addr, port);
		*reason = rsn;
	}
	return !ret;
}
