dump_addr(char *output, int maxlen, void *value, int len)
{
	struct sockaddr_in sin;
	if (len == (int)sizeof(sin)) {
		memcpy(&sin, value, len);
		snprintf(output, maxlen, "IPV4 %s:%d", ast_inet_ntoa(sin.sin_addr), ntohs(sin.sin_port));
	} else {
		ast_copy_string(output, "Invalid Address", maxlen);
	}
}
