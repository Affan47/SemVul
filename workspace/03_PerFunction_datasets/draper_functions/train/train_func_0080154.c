param_name_to_int (const gchar *pname, gint *result, gboolean *old_val)
{
	gint sum = 0;
	const gchar *ptr;

	if (!pname || ((*pname != '-') && (*pname != '+')))
		return FALSE;

	ptr = pname + 1;
	while (*ptr) {
		if ((*ptr > '9') || (*ptr < '0'))
			return FALSE;
		sum = sum * 10 + *ptr - '0';
		ptr++;
	}

	if (result)
		*result = sum;
	if (old_val)
		*old_val = (*pname == '-') ? TRUE : FALSE;

	return TRUE;
}
