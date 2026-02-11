init_funcname_len(buf, file)
    char **buf;
    const char *file;
{
    char *p;
    const char *slash;
    int len;


    for (slash = file-1; *file; file++)
#ifdef __MACOS__
	if (*file == ':') slash = file;
#else
	if (*file == '/') slash = file;
#endif

    len = strlen(FUNCNAME_PATTERN) + strlen(slash + 1);
    *buf = xmalloc(len);
    snprintf(*buf, len, FUNCNAME_PATTERN, slash + 1);
    for (p = *buf; *p; p++) {
	if (*p == '.') {
	    *p = '\0'; break;
	}
    }
    return p - *buf;
}
