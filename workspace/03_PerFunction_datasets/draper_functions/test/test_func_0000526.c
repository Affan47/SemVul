test_get_language (void)
{
	GtkSourceLanguageManager *lm;
	const gchar * const *ids;

	lm = gtk_source_language_manager_get_default ();
	ids = gtk_source_language_manager_get_language_ids (lm);
	g_assert (ids != NULL);

	while (*ids != NULL)
	{
		GtkSourceLanguage *lang1, *lang2;

		lang1 = gtk_source_language_manager_get_language (lm, *ids);
		g_assert (lang1 != NULL);
		g_assert (GTK_SOURCE_IS_LANGUAGE (lang1));
		g_assert_cmpstr (*ids, == , gtk_source_language_get_id (lang1));


		lang2 = gtk_source_language_manager_get_language (lm, *ids);
		g_assert (lang1 == lang2);

		++ids;
	}
}
