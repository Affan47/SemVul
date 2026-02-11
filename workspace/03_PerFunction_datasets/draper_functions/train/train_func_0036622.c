rev_list_view_do_copy (GiggleClipboard *clipboard)
{
	GtkClipboard *widget_clipboard;
	GList        *selection;
	GString      *text;
	const char   *sha;

	selection = giggle_rev_list_view_get_selection (GIGGLE_REV_LIST_VIEW (clipboard));
	text = g_string_new (NULL);

	while (selection) {
		if (selection->data) {
			sha = giggle_revision_get_sha (selection->data);

			if (sha) {
				if (text->len)
					g_string_append_c (text, ' ');

				g_string_append (text, sha);
			}

			g_object_unref (selection->data);
		}

		selection = g_list_delete_link (selection, selection);
	}

	if (text->len) {
		widget_clipboard = gtk_widget_get_clipboard (GTK_WIDGET (clipboard),
							     GDK_SELECTION_CLIPBOARD);
		gtk_clipboard_set_text (widget_clipboard, text->str, text->len);
	}

	g_string_free (text, TRUE);
}
