dump_ipaddr(char *output, int maxlen, void *value, int len)
{
	struct sockaddr_in sin;
	if (len == (int)sizeof(unsigned int)) {
		memcpy(&sin.sin_addr, value, len);
		snprintf(output, maxlen, "%s", ast_inet_ntoa(sin.sin_addr));
	} else
		ast_copy_string(output, "Invalid IPADDR", maxlen);
}
