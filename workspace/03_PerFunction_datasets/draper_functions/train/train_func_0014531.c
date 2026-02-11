go_data_scalar_str_unserialize (GOData *dat, char const *string, gpointer user)
{
	GODataScalarStr *str = (GODataScalarStr *)dat;

	if (str->str == string)
		return TRUE;
	if (str->needs_free)
		g_free ((char *)str->str);
	str->str = g_strdup (string);
	str->needs_free = TRUE;
	return TRUE;
}
