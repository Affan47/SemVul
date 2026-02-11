getWord(const char *ref, const char **ptr)
{
	const char *p = *ptr;

	while ((*ref != '\0') && (*p != '\0') && (*ref == *p)) ref++, p++;

	if (*ref) return FALSE;

	*ptr = p;
	return TRUE;
}
