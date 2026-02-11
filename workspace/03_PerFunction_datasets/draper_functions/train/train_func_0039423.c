resolve_host(const char *name, int hint)
{
	struct addrinfo *ai = NULL, hints;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = hint;

	if (!getaddrinfo(name, NULL, &hints, &ai) && ai) {
		char *tmp;

		tmp = xmalloc(ai->ai_addrlen);
		memcpy(tmp, ai->ai_addr, ai->ai_addrlen);

		freeaddrinfo(ai);

		return (struct sockaddr*) tmp;
	}

	return NULL;
}
