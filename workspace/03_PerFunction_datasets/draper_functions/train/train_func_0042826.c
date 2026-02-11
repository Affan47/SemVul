net_store_fill_v4 (netstore *ns, guint32 addr, int port)
{
	struct addrinfo *ai;
	struct sockaddr_in *sin;

	ai = ns->ip6_hostent;
	if (!ai) {
		ai = malloc (sizeof (struct addrinfo));
		memset (ai, 0, sizeof (struct addrinfo));
		ns->ip6_hostent = ai;
	}
	sin = (struct sockaddr_in *)ai->ai_addr;
	if (!sin) {
		sin = malloc (sizeof (struct sockaddr_in));
		memset (sin, 0, sizeof (struct sockaddr_in));
		ai->ai_addr = (struct sockaddr *)sin;
	}
	ai->ai_family = AF_INET;
	ai->ai_addrlen = sizeof(struct sockaddr_in);
	sin->sin_family = AF_INET;
	sin->sin_addr.s_addr = addr;
	sin->sin_port = port;
	ai->ai_next = NULL;
}
