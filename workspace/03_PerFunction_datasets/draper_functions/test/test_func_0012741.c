rfc822_display_hdrvalue(const char *hdrname,
			    const char *hdrvalue,
			    const char *charset,
			    void (*display_func)(const char *, size_t,
						 void *),
			    void (*err_func)(const char *, int, void *),
			    void *ptr)
{
	struct rfc822_display_hdrvalue_s s;

	s.display_func=display_func;
	s.ptr=ptr;

	if (rfc822hdr_is_addr(hdrname))
	{
		return rfc2047_print_unicode_addrstr(hdrvalue,
						     charset,
						     rfc822_display_hdrvalue_print_func,
						     rfc822_display_hdrvalue_print_separator,
						     NULL,
						     &s);
	}

	s.u=unicode_find(charset);

	if (!s.u)
	{
		unknown_charset(charset, display_func, ptr);
		return (0);
	}

	return rfc2047_decode_unicode(hdrvalue, s.u, display_func, ptr);
}
