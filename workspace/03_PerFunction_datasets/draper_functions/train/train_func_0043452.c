ciequal(register const char *ap, register const char *bp)
{
	while (lowerit(*ap) == lowerit(*bp++))
		if (*ap++ == '\0')
			return TRUE;
	return FALSE;
}
