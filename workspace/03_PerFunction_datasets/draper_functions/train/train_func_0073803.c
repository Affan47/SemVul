bsd_glob(const char *pattern, int flags,
	 int (*errfunc)(const char *, int), glob_t *pglob)
{
	const U8 *patnext;
	int c;
	Char *bufnext, *bufend, patbuf[MAXPATHLEN];
	patnext = (U8 *) pattern;

#if 0
	if (!(flags & GLOB_APPEND)) {
		pglob->gl_pathc = 0;
		pglob->gl_pathv = NULL;
		if (!(flags & GLOB_DOOFFS))
			pglob->gl_offs = 0;
	}
#else
	pglob->gl_pathc = 0;
	pglob->gl_pathv = NULL;
	pglob->gl_offs = 0;
#endif
	pglob->gl_flags = flags & ~GLOB_MAGCHAR;
	pglob->gl_errfunc = errfunc;
	pglob->gl_matchc = 0;

	bufnext = patbuf;
	bufend = bufnext + MAXPATHLEN - 1;
#ifdef DOSISH


	if (isalpha(pattern[0]) && pattern[1] == ':' &&
	    pattern[2] != BG_SEP && pattern[2] != BG_SEP2 &&
	    bufend - bufnext > 4) {
		*bufnext++ = pattern[0];
		*bufnext++ = ':';
		*bufnext++ = '.';
		*bufnext++ = BG_SEP;
		patnext += 2;
	}
#endif

	if (flags & GLOB_QUOTE) {

		while (bufnext < bufend && (c = *patnext++) != BG_EOS)
			if (c == BG_QUOTE) {
#ifdef DOSISH


				if ((c = *patnext++) != '[' && c != ']' &&
				    c != '-' && c != '{' && c != '}' &&
				    c != '~' && c != '\\') {
#else
				if ((c = *patnext++) == BG_EOS) {
#endif
					c = BG_QUOTE;
					--patnext;
				}
				*bufnext++ = c | M_PROTECT;
			} else
				*bufnext++ = c;
	} else
		while (bufnext < bufend && (c = *patnext++) != BG_EOS)
			*bufnext++ = c;
	*bufnext = BG_EOS;

	if (flags & GLOB_BRACE)
	    return globexp1(patbuf, pglob);
	else
	    return glob0(patbuf, pglob);
}
