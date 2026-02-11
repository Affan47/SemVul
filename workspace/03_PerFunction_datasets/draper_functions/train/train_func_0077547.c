vg_strdup (const char *string)
{
	if (string == NULL)
		return NULL;

	if (string[0] == '\0')
		return "";

	return vg_strpool_add ((char *) string, FALSE);
}
