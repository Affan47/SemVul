print_language_style_ids (GtkSourceLanguage *language)
{
	gchar **styles;

	g_assert (language != NULL);

	styles = gtk_source_language_get_style_ids (language);

	if (styles == NULL)
	{
		g_print ("No styles in language '%s'\n",
			 gtk_source_language_get_name (language));
	}
	else
	{
		gchar **ids;
		g_print ("Styles in language '%s':\n",
			 gtk_source_language_get_name (language));

		for (ids = styles; *ids != NULL; ids++)
		{
			const gchar *name = gtk_source_language_get_style_name (language, *ids);

			g_print ("- %s (name: '%s')\n", *ids, name);
		}

		g_strfreev (styles);
	}

	g_print ("\n");
}
