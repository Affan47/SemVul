parse_url(char *src_url, struct host_info *h)
{
	char *url, *p, *sp;

	 url = xstrdup(src_url);

	if (strncmp(url, "http://", 7) == 0) {
		h->port = bb_lookup_port("http", "tcp", 80);
		h->host = url + 7;
		h->is_ftp = 0;
	} else if (strncmp(url, "ftp://", 6) == 0) {
		h->port = bb_lookup_port("ftp", "tcp", 21);
		h->host = url + 6;
		h->is_ftp = 1;
	} else
		bb_error_msg_and_die("not an http or ftp url: %s", sanitize_string(url));


	sp = strchr(h->host, '/');
	p = strchr(h->host, '?'); if (!sp || (p && sp > p)) sp = p;
	p = strchr(h->host, '#'); if (!sp || (p && sp > p)) sp = p;
	if (!sp) {
		h->path = "";
	} else if (*sp == '/') {
		*sp = '\0';
		h->path = sp + 1;
	} else {


		memmove(h->host - 1, h->host, sp - h->host);
		h->host--;
		sp[-1] = '\0';
		h->path = sp;
	}


	sp = strrchr(h->host, '@');
	if (sp != NULL) {
		h->user = h->host;
		*sp = '\0';
		h->host = sp + 1;
	}

	sp = h->host;
}
