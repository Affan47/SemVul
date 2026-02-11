maki_ensure_string_array (gchar*** string_array)
{
	if (*string_array == NULL)
	{
		*string_array = g_new(gchar*, 1);
		(*string_array)[0] = NULL;
	}
}
