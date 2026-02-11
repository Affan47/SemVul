set_socks_server(const char *socks)
{
	struct url *url;
	enum socks_ver socksv;

	url = url_tokenize(socks);
	if (!url || !url->scheme) {
		log_error("shim: bad socks server, %s", socks);
		exit(1);
	}
	if (url->port < 0)
		url->port = 1080;

	if (!evutil_ascii_strcasecmp(url->scheme, "socks4"))
		socksv = SOCKS_4;
	else if (!evutil_ascii_strcasecmp(url->scheme, "socks4a"))
		socksv = SOCKS_4a;
	else {
		log_error("shim: unknown socks version, %s",
			  url->scheme);
		exit(1);
	}

	if (conn_set_socks_server(url->host, url->port, socksv) < 0)
		exit(1);

	url_free(url);
}
