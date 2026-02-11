logcommand_external(service_t *svs, const char *type, connection_t *source, const char *sourcedesc, myuser_t *mu, int level, const char *fmt, ...)
{
	va_list args;
	char lbuf[BUFSIZE];

	va_start(args, fmt);
	vsnprintf(lbuf, BUFSIZE, fmt, args);
	va_end(args);

	slog_ext(LOG_NONINTERACTIVE, level, "%s %s:%s(%s)[%s] %s",
			svs != NULL ? svs->nick : me.name,
			mu != NULL ? entity(mu)->name : "",
			type,
			source != NULL ? source->hbuf : "<noconn>",
			sourcedesc != NULL ? sourcedesc : "<unknown>",
			lbuf);
	slog_ext(LOG_INTERACTIVE, level, "%s <%s>%s %s",
			svs != NULL ? svs->nick : me.name,
			type,
			mu != NULL ? entity(mu)->name : "",
			lbuf);
}
