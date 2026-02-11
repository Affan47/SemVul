proxy_negotiate(int type, int fd, char *host, unsigned short port)
{
	switch (type) {
	case PT_NONE:
	    	return 0;
	case PT_PASSTHRU:
		return proxy_passthru(fd, host, port);
	case PT_HTTP:
		return proxy_http(fd, host, port);
	case PT_TELNET:
		return proxy_telnet(fd, host, port);
	case PT_SOCKS4:
		return proxy_socks4(fd, host, port, 0);
	case PT_SOCKS4A:
		return proxy_socks4(fd, host, port, 1);
	case PT_SOCKS5:
		return proxy_socks5(fd, host, port, 0);
	case PT_SOCKS5D:
		return proxy_socks5(fd, host, port, 1);
	default:
		return -1;
	}
}
