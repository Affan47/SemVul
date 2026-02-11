photos_base_item_download_in_thread_func (GTask *task,
                                          gpointer source_object,
                                          gpointer task_data,
                                          GCancellable *cancellable)
{
  PhotosBaseItem *self = PHOTOS_BASE_ITEM (source_object);
  PhotosBaseItemPrivate *priv = self->priv;
  GError *error;
  gchar *path;

  g_mutex_lock (&priv->mutex_download);

  error = NULL;
  path = photos_base_item_download (self, cancellable, &error);
  if (error != NULL)
    {
      g_task_return_error (task, error);
      goto out;
    }

  g_task_return_pointer (task, path, g_free);

 out:
  g_mutex_unlock (&priv->mutex_download);
}
