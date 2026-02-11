fs_element_added_notifier_remove (FsElementAddedNotifier *notifier,
    GstBin *bin)
{
  g_return_val_if_fail (FS_IS_ELEMENT_ADDED_NOTIFIER (notifier), FALSE);
  g_return_val_if_fail (GST_IS_BIN (bin), FALSE);

  g_ptr_array_remove (notifier->priv->bins, bin);

  if (g_signal_handler_find (bin,
          G_SIGNAL_MATCH_FUNC | G_SIGNAL_MATCH_DATA,
          0, 0, NULL,
          _element_added_callback, notifier) != 0)
  {
    _element_removed_callback (NULL, GST_ELEMENT (bin), notifier);
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}
