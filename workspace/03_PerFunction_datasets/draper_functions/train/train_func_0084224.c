parse_bool_str (const char *str)
{
	if (str == NULL)
		return FALSE;
	if (g_ascii_strcasecmp (str, "true") == 0)
		return TRUE;
	if (g_ascii_strcasecmp (str, "false") == 0)
		return FALSE;
	return atoi (str);
}
