save_string (const gchar *str,
             FILE *fp)
{
	gint rv;

	if (!str || !*str)
		return TRUE;

	rv = fwrite (str, strlen (str), 1, fp);
	return (rv == 1);
}
