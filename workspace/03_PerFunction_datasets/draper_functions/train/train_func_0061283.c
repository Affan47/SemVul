utils_atob(const gchar *str)
{
	if (G_UNLIKELY(str == NULL))
		return FALSE;
	else if (strcmp(str, "TRUE") == 0 || strcmp(str, "true") == 0)
		return TRUE;
	return FALSE;
}
