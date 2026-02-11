completion_match_selected_cb (GtkEntryCompletion *widget,
                              GtkTreeModel       *model,
                              GtkTreeIter        *iter,
                              gpointer            user_data)
{
	GthTagsEntry *self = user_data;
	const char   *tag_start;
	const char   *tag_end;
	const char   *text;
	char         *head;
	const char   *tail;
	char         *tag_name = NULL;

	get_tag_limits (self, &tag_start, &tag_end);
	text = gtk_entry_get_text (GTK_ENTRY (self->priv->entry));
	head = g_strndup (text, tag_start - text);
	head = g_strstrip (head);
	if (tag_end[0] != '\0')
		tail = g_utf8_next_char (tag_end);
	else
		tail = tag_end;
	gtk_tree_model_get (model, iter,
			    COMPLETION_NAME_COLUMN, &tag_name,
			    -1);

	if (tag_name != NULL) {
		char *new_text;

		new_text = g_strconcat (head,
					" ",
					tag_name,
					", " ,
					tail,
					NULL);
		gtk_entry_set_text (GTK_ENTRY (self->priv->entry), new_text);
		gtk_editable_set_position (GTK_EDITABLE (self->priv->entry), -1);

		g_free (new_text);
		g_free (tag_name);
	}

	g_free (head);

	return TRUE;
}
