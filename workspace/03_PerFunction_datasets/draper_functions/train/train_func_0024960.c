gda_default_escape_string (const gchar *string)
{
	gchar *ptr, *ret, *retptr;
	gint size;

	if (!string)
		return NULL;


	ptr = (gchar *) string;
	size = 1;
	while (*ptr) {
		if ((*ptr == '\'') ||(*ptr == '\\'))
			size += 2;
		else
			size += 1;
		ptr++;
	}

	ptr = (gchar *) string;
	ret = g_new0 (gchar, size);
	retptr = ret;
	while (*ptr) {
		if (*ptr == '\'') {
			*retptr = '\'';
			*(retptr+1) = *ptr;
			retptr += 2;
		}
		else if (*ptr == '\\') {
			*retptr = '\\';
			*(retptr+1) = *ptr;
			retptr += 2;
		}
		else {
			*retptr = *ptr;
			retptr ++;
		}
		ptr++;
	}
	*retptr = '\0';

	return ret;
}
