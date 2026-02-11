sock_resolve_unix(const char * addr)
{
	struct sock_addr ** sas;
	struct sock_addr * sa;
	struct sockaddr_un * sa_un;


	if ((sa_un = malloc(sizeof(struct sockaddr_un))) == NULL)
		goto err0;
	memset(sa_un, 0, sizeof(struct sockaddr_un));
	sa_un->sun_family = AF_UNIX;
	if (strlen(addr) >= sizeof(sa_un->sun_path)) {
		warn0("socket path too long: %s", addr);
		goto err1;
	}
	strcpy(sa_un->sun_path, addr);


	if ((sa = malloc(sizeof(struct sock_addr))) == NULL)
		goto err1;
	sa->ai_family = AF_UNIX;
	sa->ai_socktype = SOCK_STREAM;
	sa->name = (struct sockaddr *)sa_un;
	sa->namelen = sizeof(struct sockaddr_un);


	if ((sas = malloc(2 * sizeof(struct sock_addr *))) == NULL)
		goto err2;
	sas[0] = sa;
	sas[1] = NULL;


	return (sas);

err2:
	free(sa);
err1:
	free(sa_un);
err0:

	return (NULL);
}
