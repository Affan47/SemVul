ne_debug(int ch, const char *template, ...)
{
    va_list params;
    if ((ch & ne_debug_mask) == 0) return;
    fflush(stdout);
    va_start(params, template);
    vfprintf(ne_debug_stream, template, params);
    va_end(params);
    if ((ch & NE_DBG_FLUSH) == NE_DBG_FLUSH)
	fflush(ne_debug_stream);
}
