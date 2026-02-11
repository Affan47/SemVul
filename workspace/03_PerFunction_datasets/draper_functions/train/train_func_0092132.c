_gedit_tab_get_name (GeditTab *tab)
{
	GeditDocument *doc;
	gchar *name;
	gchar *docname;
	gchar *tab_name;

	g_return_val_if_fail (GEDIT_IS_TAB (tab), NULL);

	doc = gedit_tab_get_document (tab);

	name = gedit_document_get_short_name_for_display (doc);


	docname = gedit_utils_str_middle_truncate (name, MAX_DOC_NAME_LENGTH);

	if (gtk_text_buffer_get_modified (GTK_TEXT_BUFFER (doc)))
	{
		tab_name = g_strdup_printf ("*%s", docname);
	}
	else
	{
 #if 0
		if (gedit_document_get_readonly (doc))
		{
			tab_name = g_strdup_printf ("%s [%s]", docname,
						 _("RO"));
		}
		else
		{
			tab_name = g_strdup_printf ("%s", docname);
		}
#endif
		tab_name = g_strdup (docname);
	}

	g_free (docname);
	g_free (name);

	return tab_name;
}
