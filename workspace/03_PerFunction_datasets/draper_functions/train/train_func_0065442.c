about_free_credit(void)
{
	gint i = 0;

	gchar** ptr = (gchar**) authors;
	for(i=0; ptr[i]; i++)
		g_free (ptr[i]);
	ptr = (gchar**) documenters;
	for(i=0; ptr[i]; i++)
		g_free (ptr[i]);

	g_free(translators);
}
