is_helper (const gchar *ps1,
           const gchar *ps2)
{
	gchar *s1 = e_util_utf8_remove_accents (ps1);
	gchar *s2 = e_util_utf8_remove_accents (ps2);
	gchar *res;

	if (!e_util_utf8_strcasecmp (s1, s2))
		res = (gchar *) ps1;
	else
		res = NULL;

	g_free (s1);
	g_free (s2);

	return res;
}
