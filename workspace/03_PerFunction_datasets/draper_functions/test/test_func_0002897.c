guess_category_value (const gchar *categoryname)
{
	const gchar *retval;


	retval = g_getenv (categoryname);
	if (retval != NULL && retval[0] != '\0')
		return retval;


	retval = g_getenv ("LANGUAGE");
	if (retval != NULL && retval[0] != '\0')
		return retval;


	retval = g_getenv ("LC_ALL");
	if (retval != NULL && retval[0] != '\0')
		return retval;


	retval = g_getenv ("LANG");
	if (retval != NULL && retval[0] != '\0')
		return retval;

	return NULL;
}
