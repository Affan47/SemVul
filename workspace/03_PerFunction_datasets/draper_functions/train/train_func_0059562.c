handle_datagram(void *arg)
{
	request_t	*req;
	char		**fp;
	char		*key;
	char		*value;
	char		*end;
	int			 err;

	req = (request_t *)arg;
	key = req->data;


	while (key < (req->data + req->datalen)) {
		end = key + strcspn(key, "\r\n");
		*end = '\0';
		value = strchr(key, '=');


		if (!value)
			continue;

		*value++ = '\0';
		fp = find_field(req, key);
		if (fp != NULL)
			*fp = value;
		else
			 ;

		key = end + 1;
		while (key < (req->data + req->datalen)) {
			if (strchr("\r\n", *key))
				key++;
			else
				break;
		}
	}

	request_handle(req);

#ifdef DEBUG
	printf("Target address length is %d: %s:%d\n", req->addrlen,
					inet_ntoa(req->addr.in.sin_addr),
					req->addr.in.sin_port);
#endif

	printf("- %s\n", req->sender); fflush(stdout);
	err = sendto(req->sock, req->fmt, req->fmtlen, 0,
			(struct sockaddr *)(&req->addr.in), req->addrlen);
	if (err == -1)
		perror("sendto");

	FREE_RESPONSE(req->spf_response);
	FREE_REQUEST(req->spf_request);

	FREE_STRING(req->data);
	free(arg);
	return NULL;
}
