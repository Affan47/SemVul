cf_log_info(CONF_SECTION *cs, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	if (debug_flag > 1 && cf_log_config && cs) vradlog(L_DBG, fmt, ap);
	va_end(ap);
}
