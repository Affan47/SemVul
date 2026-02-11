_g_strset (char       **s,
	   const char  *value)
{
	if (*s == value)
		return;

	if (*s != NULL) {
		g_free (*s);
		*s = NULL;
	}

	if (value != NULL)
		*s = g_strdup (value);
}
