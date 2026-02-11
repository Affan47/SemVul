inf_text_gtk_buffer_delete_range_cb_after(GtkTextBuffer* gtk_buffer,
                                          GtkTextIter* begin,
                                          GtkTextIter* end,
                                          gpointer user_data)
{
  InfTextGtkBuffer* buffer;
  InfTextGtkBufferPrivate* priv;

  buffer = INF_TEXT_GTK_BUFFER(user_data);
  priv = INF_TEXT_GTK_BUFFER_PRIVATE(buffer);

  g_assert(priv->record != NULL);
  g_assert(priv->record->insert == FALSE);

  g_assert(priv->record->applied == TRUE ||
           priv->record->position == (guint)gtk_text_iter_get_offset(begin));

  inf_text_gtk_buffer_pop_record(buffer);
}
