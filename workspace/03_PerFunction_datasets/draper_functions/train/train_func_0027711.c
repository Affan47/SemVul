empathy_about_dialog_new (GtkWindow *parent)
{
	GString *license_trans = g_string_new (NULL);
	int i;

	for (i = 0; license[i] != NULL; i++) {
		g_string_append (license_trans, _(license[i]));
		g_string_append (license_trans, "\n\n");

	}
	gtk_show_about_dialog (parent,
			       "artists", artists,
			       "authors", authors,
			       "comments", _("An Instant Messaging client for GNOME"),
			       "license", license_trans->str,
			       "wrap-license", TRUE,
			       "copyright", "Imendio AB 2002-2007\nCollabora Ltd 2007-2011",
			       "documenters", documenters,
			       "logo-icon-name", "empathy",
			       "translator-credits", _("translator-credits"),
			       "version", PACKAGE_VERSION,
			       "website", WEB_SITE,
			       NULL);

	g_string_free (license_trans, TRUE);
}
