champlain_file_cache_set_property (GObject *object,
    guint property_id,
    const GValue *value,
    GParamSpec *pspec)
{
  ChamplainFileCache *file_cache = CHAMPLAIN_FILE_CACHE (object);
  ChamplainFileCachePrivate *priv = file_cache->priv;

  switch (property_id)
    {
    case PROP_SIZE_LIMIT:
      champlain_file_cache_set_size_limit (file_cache, g_value_get_uint (value));
      break;

    case PROP_CACHE_DIR:
      if (priv->cache_dir)
        g_free (priv->cache_dir);
      priv->cache_dir = g_strdup (g_value_get_string (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    }
}
