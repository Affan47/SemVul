inf_text_gtk_buffer_buffer_get_modified(InfBuffer* buffer)
{
  InfTextGtkBuffer* gtk_buffer;
  InfTextGtkBufferPrivate* priv;

  gtk_buffer = INF_TEXT_GTK_BUFFER(buffer);
  priv = INF_TEXT_GTK_BUFFER_PRIVATE(gtk_buffer);

  if(priv->buffer != NULL)
    return gtk_text_buffer_get_modified(priv->buffer);
  else
    return FALSE;
}
