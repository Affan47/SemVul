get_suffix_from_basename (const char *basename)
{
	char *suffix;
	char *suffix_start;
	guint len;


	suffix_start = g_utf8_strrchr (basename, -1, '.');

	if (suffix_start == NULL)
		return NULL;

	len = strlen (suffix_start) - 1;
	suffix = g_strndup (suffix_start+1, len);

	return suffix;

}
