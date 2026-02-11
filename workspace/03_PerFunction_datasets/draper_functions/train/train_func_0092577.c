gnumeric_rightb (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	const guchar *peek = (const guchar *)value_peek_string (argv[0]);
	gnm_float count = argv[1] ? value_get_as_float (argv[1]) : 1.0;
	int len = strlen (peek);
	int icount;
	gchar *res;

	if (count < 0)
		return value_new_error_VALUE (ei->pos);
	icount = (int)MIN ((gnm_float)INT_MAX, count);
	if (icount >= len)
		return value_new_string (peek);

	res = g_utf8_find_next_char (peek + len - icount - 1, peek + len);
	return value_new_string ((res == NULL) ? "" : res);
}
