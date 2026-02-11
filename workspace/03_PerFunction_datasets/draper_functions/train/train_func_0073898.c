str_to_gint32(char *s, gint32* pint)
{
	char    *endptr;
	long	integer;

	errno = 0;
	integer = strtol(s, &endptr, 0);

	if (errno == EINVAL || endptr == s || *endptr != '\0') {

		dfilter_fail("\"%s\" is not a valid number.", s);
		return FALSE;
	}
	if (errno == ERANGE) {
		if (integer == LONG_MAX) {
			dfilter_fail("\"%s\" causes an integer overflow.", s);
		}
		else if (integer == LONG_MIN) {
			dfilter_fail("\"%s\" causes an integer underflow.", s);
		}
		else {


			dfilter_fail("\"%s\" is not an integer.", s);
		}
		return FALSE;
	}
	if (integer > G_MAXINT32) {


		dfilter_fail("\"%s\" causes an integer overflow.", s);
		return FALSE;
	}
	if (integer < G_MININT32) {


		dfilter_fail("\"%s\" causes an integer underflow.", s);
		return FALSE;
	}

	*pint = (gint32)integer;
	return TRUE;
}
