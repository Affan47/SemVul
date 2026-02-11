on_font_changed (GtkButton* button,
                 gpointer data)
{
  ChatArea* self = NULL;
  GtkTextBuffer *buffer = NULL;
  GtkTextMark* mark = NULL;
  GtkTextMark* mark_at_insert = NULL;
  GtkTextMark* mark_at_bound = NULL;
  GtkTextIter start;
  GtkTextIter end;
  GtkTextIter iter_sav_insert;
  GtkTextIter iter_sav_bound;

  const gchar* opening_tag = NULL;
  const gchar* closing_tag = NULL;
  gchar* tags = NULL;

  self = (ChatArea*)data;


  opening_tag = (const gchar*) g_object_get_data (G_OBJECT (button),
						  "gm_open_tag");
  closing_tag = (const gchar*) g_object_get_data (G_OBJECT (button),
						  "gm_close_tag");
  tags = g_strdup_printf ("%s%s", opening_tag, closing_tag);

  buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (self->priv->message));
  if (gtk_text_buffer_get_selection_bounds (buffer, &start, &end)) {


    gtk_text_buffer_get_iter_at_mark (buffer, &iter_sav_insert,
				      gtk_text_buffer_get_insert (buffer));
    gtk_text_buffer_get_iter_at_mark (buffer, &iter_sav_bound,
				      gtk_text_buffer_get_selection_bound (buffer));
    if (gtk_text_iter_compare (&iter_sav_bound, &iter_sav_insert) < 0) {

      mark_at_bound = gtk_text_buffer_create_mark (buffer, NULL,
						   &iter_sav_bound, FALSE);
      mark_at_insert = gtk_text_buffer_create_mark (buffer, NULL,
						    &iter_sav_insert, TRUE);
      mark = mark_at_insert;
    } else {

      mark_at_bound = gtk_text_buffer_create_mark (buffer, NULL,
						   &iter_sav_bound, TRUE);
      mark_at_insert = gtk_text_buffer_create_mark (buffer, NULL,
						    &iter_sav_insert, FALSE);
      mark = mark_at_bound;
    }


    gtk_text_buffer_insert (buffer, &start, opening_tag, -1);
    gtk_text_buffer_get_iter_at_mark (buffer, &end, mark);
    gtk_text_buffer_insert (buffer, &end, closing_tag, -1);


    gtk_text_buffer_get_iter_at_mark (buffer, &iter_sav_bound, mark_at_bound);
    gtk_text_buffer_get_iter_at_mark (buffer, &iter_sav_insert, mark_at_insert);
    gtk_text_buffer_move_mark_by_name (buffer, "selection_bound", &iter_sav_bound);
    gtk_text_buffer_move_mark_by_name (buffer, "insert", &iter_sav_insert);
  }
  else {

    gtk_text_buffer_get_iter_at_mark (buffer, &end,
				      gtk_text_buffer_get_insert (buffer));
    gtk_text_buffer_insert (buffer, &end, tags, -1);
    gtk_text_iter_backward_chars (&end, strlen (closing_tag));
    gtk_text_buffer_place_cursor (buffer, &end);
  }

  g_free (tags);

  gtk_widget_grab_focus (self->priv->message);
}
