stu_utf8_find(const gchar *string, gboolean (*function)(gunichar ch, gpointer user), gpointer user)
{
	if(string == NULL || function == NULL)
		return NULL;

	while(*string != '\0')
	{
		gunichar	here = g_utf8_get_char(string);

		if(function(here, user))
			return string;
		string = g_utf8_next_char(string);
	}
	return NULL;
}
