__repmgr_getaddr(env, host, port, flags, result)
	ENV *env;
	const char *host;
	u_int port;
	int flags;
	ADDRINFO **result;
{
	ADDRINFO *answer, hints;
	char buffer[10];


	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = flags;
	(void)snprintf(buffer, sizeof(buffer), "%u", port);


	if (__os_getaddrinfo(env, host, port, buffer, &hints, &answer) != 0)
		return (DB_REP_UNAVAIL);
	*result = answer;

	return (0);
}
