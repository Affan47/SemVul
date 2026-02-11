getaddrinfo_unix(const char *path, const struct addrinfo * hintsp,
				 struct addrinfo ** result)
{
	struct addrinfo hints;
	struct addrinfo *aip;
	struct sockaddr_un *unp;

	*result = NULL;

	MemSet(&hints, 0, sizeof(hints));

	if (strlen(path) >= sizeof(unp->sun_path))
		return EAI_FAIL;

	if (hintsp == NULL)
	{
		hints.ai_family = AF_UNIX;
		hints.ai_socktype = SOCK_STREAM;
	}
	else
		memcpy(&hints, hintsp, sizeof(hints));

	if (hints.ai_socktype == 0)
		hints.ai_socktype = SOCK_STREAM;

	if (hints.ai_family != AF_UNIX)
	{

		return EAI_FAIL;
	}

	aip = calloc(1, sizeof(struct addrinfo));
	if (aip == NULL)
		return EAI_MEMORY;

	unp = calloc(1, sizeof(struct sockaddr_un));
	if (unp == NULL)
	{
		free(aip);
		return EAI_MEMORY;
	}

	aip->ai_family = AF_UNIX;
	aip->ai_socktype = hints.ai_socktype;
	aip->ai_protocol = hints.ai_protocol;
	aip->ai_next = NULL;
	aip->ai_canonname = NULL;
	*result = aip;

	unp->sun_family = AF_UNIX;
	aip->ai_addr = (struct sockaddr *) unp;
	aip->ai_addrlen = sizeof(struct sockaddr_un);

	strcpy(unp->sun_path, path);

#ifdef HAVE_STRUCT_SOCKADDR_STORAGE_SS_LEN
	unp->sun_len = sizeof(struct sockaddr_un);
#endif

	return 0;
}
