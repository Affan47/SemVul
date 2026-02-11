cb_cell_comment_ok_clicked (G_GNUC_UNUSED GtkWidget *button,
			    CommentState *state)
{
	char          *text;
	PangoAttrList *attr;
	char const *author;

	author = gtk_entry_get_text
		(GTK_ENTRY (go_gtk_builder_get_widget
			    (state->gui, "new-author-entry")));
	g_object_get (G_OBJECT (state->gtv), "text", &text,
		      "attributes", &attr, NULL);
	if (!cmd_set_comment (WORKBOOK_CONTROL (state->wbcg),
			      state->sheet, state->pos, text, attr, author))
		gtk_widget_destroy (state->dialog);
	g_free (text);
	pango_attr_list_unref (attr);
}
