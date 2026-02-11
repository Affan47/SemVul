setup_sensitivity (PagerData *pager,
		   GtkBuilder *builder,
		   const char *wid1,
		   const char *wid2,
		   const char *wid3,
		   const char *key)
{
	GtkWidget *w;

	if (g_settings_is_writable (pager->settings, key)) {
		return;
	}

	w = WID (wid1);
	g_assert (w != NULL);
	g_object_set_data (G_OBJECT (w), NEVER_SENSITIVE,
			   GINT_TO_POINTER (1));
	gtk_widget_set_sensitive (w, FALSE);

	if (wid2 != NULL) {
		w = WID (wid2);
		g_assert (w != NULL);
		g_object_set_data (G_OBJECT (w), NEVER_SENSITIVE,
				   GINT_TO_POINTER (1));
		gtk_widget_set_sensitive (w, FALSE);
	}
	if (wid3 != NULL) {
		w = WID (wid3);
		g_assert (w != NULL);
		g_object_set_data (G_OBJECT (w), NEVER_SENSITIVE,
				   GINT_TO_POINTER (1));
		gtk_widget_set_sensitive (w, FALSE);
	}

}
