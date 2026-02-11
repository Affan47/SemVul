_wapi_glob(GDir *dir, const char *pattern, int flags, wapi_glob_t *pglob)
{
	const u_char *patnext;
	int c;
	gchar *bufnext, *bufend, patbuf[PATH_MAX];

	patnext = (u_char *) pattern;
	if (!(flags & WAPI_GLOB_APPEND)) {
		pglob->gl_pathc = 0;
		pglob->gl_pathv = NULL;
		pglob->gl_offs = 0;
	}
	pglob->gl_flags = flags & ~WAPI_GLOB_MAGCHAR;

	bufnext = patbuf;
	bufend = bufnext + PATH_MAX - 1;


	while (bufnext < bufend && (c = *patnext++) != EOS)
		if (c == QUOTE) {
			if ((c = *patnext++) == EOS) {
				c = QUOTE;
				--patnext;
			}
			*bufnext++ = c | M_PROTECT;
		} else
			*bufnext++ = c;

	*bufnext = EOS;

	return glob0(dir, patbuf, pglob, flags & WAPI_GLOB_IGNORECASE,
		     flags & WAPI_GLOB_UNIQUE);
}
