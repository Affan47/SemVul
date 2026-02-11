dump (GSList const *args)
{
	GSList const	*iter;
	GString		*str;

	str = g_string_new (NULL);

	for ( iter = args; iter != NULL; iter = iter->next) {
		g_string_append (str, (char const *) iter->data);
	}

	return g_string_free (str, false);
}
