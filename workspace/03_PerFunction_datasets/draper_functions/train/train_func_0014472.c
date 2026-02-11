rfc2047_encode_header_tobuf(const char *name,
				  const char *header,
				  const char *charset)
{
	if (rfc822hdr_is_addr(name))
	{
		char *s=0;

		struct rfc822t *t;
		struct rfc822a *a;

		if ((t=rfc822t_alloc_new(header, NULL, NULL)) != 0)
		{
			if ((a=rfc822a_alloc(t)) != 0)
			{
				s=rfc2047_encode_header_addr(a, charset);
				rfc822a_free(a);
			}
			rfc822t_free(t);
		}
		return s;
	}

	return rfc2047_encode_str(header, charset, rfc2047_qp_allow_word);
}
