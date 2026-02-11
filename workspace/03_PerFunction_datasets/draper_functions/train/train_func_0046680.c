inf_gtk_io_finalize(GObject* object)
{
  InfGtkIo* io;
  InfGtkIoPrivate* priv;
  GSList* item;
  int mutexref;

  io = INF_GTK_IO(object);
  priv = INF_GTK_IO_PRIVATE(io);

  g_mutex_lock(priv->mutex);

  for(item = priv->watches; item != NULL; item = g_slist_next(item))
  {

    g_assert( ((InfIoWatch*)item->data)->executing == FALSE);

    if( ((InfIoWatch*)item->data)->id != 0)
      g_source_remove( ((InfIoWatch*)item->data)->id);
    inf_gtk_io_watch_free((InfIoWatch*)item->data);
  }
  g_slist_free(priv->watches);

  for(item = priv->timeouts; item != NULL; item = g_slist_next(item))
  {
    if( ((InfIoTimeout*)item->data)->id != 0)
      g_source_remove( ((InfIoTimeout*)item->data)->id);
    inf_gtk_io_timeout_free((InfIoTimeout*)item->data);
  }
  g_slist_free(priv->timeouts);

  for(item = priv->dispatchs; item != NULL; item = g_slist_next(item))
  {
    if( ((InfIoDispatch*)item->data)->id != 0)
      g_source_remove( ((InfIoDispatch*)item->data)->id);
    inf_gtk_io_dispatch_free((InfIoDispatch*)item->data);
  }
  g_slist_free(priv->dispatchs);
  g_mutex_unlock(priv->mutex);


  if(g_atomic_int_dec_and_test(priv->mutexref))
  {
    g_mutex_free(priv->mutex);
    g_free(priv->mutexref);
  }

  G_OBJECT_CLASS(parent_class)->finalize(object);
}
