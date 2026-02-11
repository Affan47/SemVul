gitg_encoding_get_candidates (void)
{
	static GSList *ret = NULL;

	if (ret == NULL)
	{
		ret = g_slist_prepend (ret,
		                       (gpointer)gitg_encoding_get_from_index (GITG_ENCODING_WINDOWS_1250));

		ret = g_slist_prepend (ret,
		                       (gpointer)gitg_encoding_get_from_index (GITG_ENCODING_ISO_8859_1));

		ret = g_slist_prepend (ret,
		                       (gpointer)gitg_encoding_get_current ());

		ret = g_slist_prepend (ret,
		                       (gpointer)gitg_encoding_get_utf8 ());
	}

	return ret;
}
