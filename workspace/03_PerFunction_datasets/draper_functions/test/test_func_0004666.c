hash_value_destroy (GnlCompositionEntry * entry)
{
  if (entry->starthandler)
    g_signal_handler_disconnect (entry->object, entry->starthandler);
  if (entry->stophandler)
    g_signal_handler_disconnect (entry->object, entry->stophandler);
  if (entry->priorityhandler)
    g_signal_handler_disconnect (entry->object, entry->priorityhandler);
  g_signal_handler_disconnect (entry->object, entry->activehandler);
  g_signal_handler_disconnect (entry->object, entry->padremovedhandler);
  g_signal_handler_disconnect (entry->object, entry->padaddedhandler);

  if (entry->nomorepadshandler)
    g_signal_handler_disconnect (entry->object, entry->nomorepadshandler);
  g_slice_free (GnlCompositionEntry, entry);
}
