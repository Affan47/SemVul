photos_camera_cache_cursor_next (GObject *source_object, GAsyncResult *res, gpointer user_data)
{
  GTask *task = G_TASK (user_data);
  PhotosCameraCache *self;
  PhotosCameraCachePrivate *priv;
  TrackerSparqlCursor *cursor = TRACKER_SPARQL_CURSOR (source_object);
  GError *error;
  const gchar *manufacturer;
  const gchar *model;
  gchar *camera;
  gpointer key;

  self = PHOTOS_CAMERA_CACHE (g_task_get_source_object (task));
  priv = self->priv;

  error = NULL;
  tracker_sparql_cursor_next_finish (cursor, res, &error);
  if (error != NULL)
    {
      g_task_return_error (task, error);
      goto out;
    }

  manufacturer = tracker_sparql_cursor_get_string (cursor, 0, NULL);
  model = tracker_sparql_cursor_get_string (cursor, 1, NULL);

  if (manufacturer == NULL && model == NULL)
    camera = NULL;
  else if (manufacturer == NULL || g_str_has_prefix (model, manufacturer))
    camera = g_strdup (model);
  else if (model == NULL)
    camera = g_strdup (manufacturer);
  else
    camera = g_strconcat (manufacturer, " ", model, NULL);

  key = g_task_get_task_data (task);
  g_hash_table_insert (priv->cache, key, camera);

  g_task_return_pointer (task, g_strdup (camera), g_free);

 out:
  tracker_sparql_cursor_close (cursor);
  g_object_unref (task);
}
