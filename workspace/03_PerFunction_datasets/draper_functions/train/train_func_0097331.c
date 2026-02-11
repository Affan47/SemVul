gpk_update_viewer_textview_follow_link (GtkWidget *text_view, GtkTextIter *iter)
{
	GSList *tags = NULL, *tagp = NULL;

	tags = gtk_text_iter_get_tags (iter);
	for (tagp = tags; tagp != NULL; tagp = tagp->next) {
		GtkTextTag *tag = tagp->data;
		const gchar *href = (const gchar *) (g_object_get_data (G_OBJECT (tag), "href"));
		if (href != NULL)
			gpk_gnome_open (href);
	}

	if (tags != NULL)
		g_slist_free (tags);
}
