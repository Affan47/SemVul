_ast_sockaddr_to_sin(const struct ast_sockaddr *addr,
			struct sockaddr_in *sin, const char *file, int line, const char *func)
{
	if (ast_sockaddr_isnull(addr)) {
		memset(sin, 0, sizeof(*sin));
		return 1;
	}

	if (addr->len != sizeof(*sin)) {
		ast_log(__LOG_ERROR, file, line, func, "Bad address cast to IPv4\n");
		return 0;
	}

	if (addr->ss.ss_family != AF_INET && option_debug >= 1) {
		ast_log(__LOG_DEBUG, file, line, func, "Address family is not AF_INET\n");
	}

	*sin = *(struct sockaddr_in *)&addr->ss;
	return 1;
}
