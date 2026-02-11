inf_gtk_io_watch_lookup(InfGtkIo* io,
                        InfNativeSocket* socket)
{
  InfGtkIoPrivate* priv;
  GSList* item;

  priv = INF_GTK_IO_PRIVATE(io);

  for(item = priv->watches; item != NULL; item = g_slist_next(item))
    if( ((InfIoWatch*)item->data)->socket == socket)
      return (InfIoWatch*)item->data;

  return NULL;
}
