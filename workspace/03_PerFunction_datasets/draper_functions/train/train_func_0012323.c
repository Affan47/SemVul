log_warn(const char *token, const char *emsg, ...)
{
	char	*nfmt;
	va_list	 ap;


	if (emsg == NULL)
		logit(LOG_WARNING, "%s", strerror(errno));
	else {
		va_start(ap, emsg);

		if (asprintf(&nfmt, "%s: %s", emsg, strerror(errno)) == -1) {

			vlog(LOG_WARNING, token, emsg, ap);
			logit(LOG_WARNING, "%s", strerror(errno));
		} else {
			vlog(LOG_WARNING, token, nfmt, ap);
			free(nfmt);
		}
		va_end(ap);
	}
}
