e2_utils_strcat (const gchar *string1, const gchar *string2)
{
	gint len1 = strlen (string1);
	gint len2 = strlen (string2) + sizeof (gchar);
	gchar *result = g_try_malloc (len1 + len2);
	if (result != NULL)
	{
#ifdef __USE_GNU
		gchar *next = mempcpy (result, string1, len1);
		next = mempcpy (next, string2, len2);
#else
		memcpy (result, string1, len1);
		memcpy (result + len1, string2, len2);
#endif
	}
	return result;
}
