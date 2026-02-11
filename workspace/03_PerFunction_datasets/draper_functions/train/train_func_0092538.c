gnumeric_replace (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	char const *old = value_peek_string (argv[0]);
	gnm_float start = value_get_as_float (argv[1]);
	gnm_float num = value_get_as_float (argv[2]);
	char const *new = value_peek_string (argv[3]);
	size_t istart, inum, oldlen, precutlen, postcutlen, newlen;
	char const *p, *q;
	char *res;

	if (start < 1 || num < 0)
		return value_new_error_VALUE (ei->pos);

	oldlen = g_utf8_strlen (old, -1);

	istart = (int)MIN ((gnm_float)oldlen, start - 1);
	inum = (int)MIN((gnm_float)(oldlen - istart), num);


	p = g_utf8_offset_to_pointer (old, istart);
	q = g_utf8_offset_to_pointer (p, inum);

	precutlen = p - old;
	postcutlen = strlen (q);
	newlen = strlen (new);

	res = g_malloc (precutlen + newlen + postcutlen + 1);
	memcpy (res, old, precutlen);
	memcpy (res + precutlen, new, newlen);
	memcpy (res + precutlen + newlen, q, postcutlen + 1);
	return value_new_string_nocopy (res);
}
