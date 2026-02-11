__repmgr_start_connect(env, socket_result, ai, err)
	ENV *env;
	socket_t *socket_result;
	ADDRINFO *ai;
	int *err;
{
	socket_t s;
	int ret;

	if ((s = socket(ai->ai_family,
		    ai->ai_socktype, ai->ai_protocol)) == SOCKET_ERROR) {
		ret = net_errno;
		__db_err(env, ret, "create socket");
		return (ret);
	}

	if (connect(s, ai->ai_addr, (socklen_t)ai->ai_addrlen) != 0) {
		*err = net_errno;
		(void)closesocket(s);
		return (DB_REP_UNAVAIL);
	}
	RPRINT(env, (env, DB_VERB_REPMGR_MISC, "connection established"));

	*socket_result = s;
	return (0);
}
