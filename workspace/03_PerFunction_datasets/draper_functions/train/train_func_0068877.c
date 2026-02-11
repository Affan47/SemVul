gg_change_passwd4(uin_t uin, const char *email, const char *passwd, const char *newpasswd, const char *tokenid, const char *tokenval, int async)
{
	struct gg_http *h;
	char *form, *query, *__email, *__fmpwd, *__pwd, *__tokenid, *__tokenval;

	if (!uin || !email || !passwd || !newpasswd || !tokenid || !tokenval) {
		gg_debug(GG_DEBUG_MISC, "=> change, NULL parameter\n");
		errno = EFAULT;
		return NULL;
	}

	__fmpwd = gg_urlencode(passwd);
	__pwd = gg_urlencode(newpasswd);
	__email = gg_urlencode(email);
	__tokenid = gg_urlencode(tokenid);
	__tokenval = gg_urlencode(tokenval);

	if (!__fmpwd || !__pwd || !__email || !__tokenid || !__tokenval) {
		gg_debug(GG_DEBUG_MISC, "=> change, not enough memory for form fields\n");
		free(__fmpwd);
		free(__pwd);
		free(__email);
		free(__tokenid);
		free(__tokenval);
		return NULL;
	}

	if (!(form = gg_saprintf("fmnumber=%d&fmpwd=%s&pwd=%s&email=%s&tokenid=%s&tokenval=%s&code=%u", uin, __fmpwd, __pwd, __email, __tokenid, __tokenval, gg_http_hash("ss", email, newpasswd)))) {
		gg_debug(GG_DEBUG_MISC, "=> change, not enough memory for form fields\n");
		free(__fmpwd);
		free(__pwd);
		free(__email);
		free(__tokenid);
		free(__tokenval);

		return NULL;
	}

	free(__fmpwd);
	free(__pwd);
	free(__email);
	free(__tokenid);
	free(__tokenval);

	gg_debug(GG_DEBUG_MISC, "=> change, %s\n", form);

	query = gg_saprintf(
		"Host: " GG_REGISTER_HOST "\r\n"
		"Content-Type: application/x-www-form-urlencoded\r\n"
		"User-Agent: " GG_HTTP_USERAGENT "\r\n"
		"Content-Length: %d\r\n"
		"Pragma: no-cache\r\n"
		"\r\n"
		"%s",
		(int) strlen(form), form);

	free(form);

	if (!query) {
		gg_debug(GG_DEBUG_MISC, "=> change, not enough memory for query\n");
		return NULL;
	}

	if (!(h = gg_http_connect(GG_REGISTER_HOST, GG_REGISTER_PORT, async, "POST", "/appsvc/fmregister3.asp", query))) {
		gg_debug(GG_DEBUG_MISC, "=> change, gg_http_connect() failed mysteriously\n");
		free(query);
		return NULL;
	}

	h->type = GG_SESSION_PASSWD;

	free(query);

	h->callback = gg_pubdir_watch_fd;
	h->destroy = gg_pubdir_free;

	if (!async)
		gg_pubdir_watch_fd(h);

	return h;
}
