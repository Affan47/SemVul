sapi_get_default_content_type(TSRMLS_D)
{
	char *mimetype, *charset, *content_type;

	mimetype = SG(default_mimetype) ? SG(default_mimetype) : SAPI_DEFAULT_MIMETYPE;
	charset = SG(default_charset) ? SG(default_charset) : SAPI_DEFAULT_CHARSET;

	if (strncasecmp(mimetype, "text/", 5) == 0 && *charset) {
		int len = strlen(mimetype) + sizeof("; charset=") + strlen(charset);
		content_type = emalloc(len);
		snprintf(content_type, len, "%s; charset=%s", mimetype, charset);
	} else {
		content_type = estrdup(mimetype);
	}
	return content_type;
}
