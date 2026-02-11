key_release_event (GtkWidget *text_view,
		   GdkEventKey *event)
{
  GtkTextIter iter_start, iter_end;
  GtkTextBuffer *buffer;

  {
    GSList *tags = NULL, *tagp = NULL;

    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text_view));

    gtk_text_buffer_get_iter_at_mark(buffer,
				     &iter_start,
				     gtk_text_buffer_get_insert (buffer));
    gtk_text_iter_set_line_offset(&iter_start, 0);

    iter_end = iter_start;
    gtk_text_iter_forward_to_line_end(&iter_end);

    tags = gtk_text_iter_get_tags (&iter_start);

    if(g_slist_length(tags) == 0)
      {
	gtk_text_iter_backward_char (&iter_end);
	tags = gtk_text_iter_get_tags (&iter_end);
	gtk_text_iter_forward_char (&iter_end);
      }

    for (tagp = tags;  tagp != NULL;  tagp = tagp->next)
      {
	GtkTextTag *tag = tagp->data;
	gchar *name;
	g_object_get (G_OBJECT (tag), "name", &name, NULL);

	set_default_tag(buffer, tag);
	gtk_text_buffer_apply_tag_by_name(buffer,
					  name,
					  &iter_start,
					  &iter_end);
	g_free(name);
	selected_tag = NULL;
      }

    if (tags)
      g_slist_free (tags);
    else
      {

	if(selected_tag)
	  {
	    set_default_tag(buffer, selected_tag);

	    gtk_text_buffer_apply_tag(buffer,
				      selected_tag,
				      &iter_start,
				      &iter_end);
	  }
	else
	  {
	    set_default_tag(buffer, tag_list[NUMBER_OF_STYLE-1]);

	    gtk_text_buffer_apply_tag(buffer,
				      tag_list[NUMBER_OF_STYLE-1],
				      &iter_start,
				      &iter_end);
	  }
      }
  }

  return FALSE;
}
