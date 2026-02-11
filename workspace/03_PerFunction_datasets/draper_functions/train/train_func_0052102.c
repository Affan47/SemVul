mx_texture_cache_get_item (MxTextureCache *self,
                           const gchar    *uri,
                           gboolean        create_if_not_exists)
{
  MxTextureCachePrivate *priv;
  MxTextureCacheItem *item;
  gchar *new_file, *new_uri;
  const gchar *file = NULL;

  priv = TEXTURE_CACHE_PRIVATE (self);


  new_file = new_uri = NULL;

  if (g_regex_match (priv->is_uri, uri, 0, NULL))
    {
      if (create_if_not_exists)
        {
          file = new_file = mx_texture_cache_uri_to_filename (uri);
          if (!new_file)
            return NULL;
        }
    }
  else
    {
      file = uri;
      uri = new_uri = mx_texture_cache_filename_to_uri (file);
      if (!new_uri)
        return NULL;
    }

  item = g_hash_table_lookup (priv->cache, uri);

  if ((!item || !item->ptr) && create_if_not_exists)
    {
      gboolean created;
      GError *err = NULL;

      if (!item)
        {
          item = mx_texture_cache_item_new ();
          created = TRUE;
        }
      else
        created = FALSE;

      item->ptr = cogl_texture_new_from_file (file, COGL_TEXTURE_NONE,
                                              COGL_PIXEL_FORMAT_ANY,
                                              &err);

      if (!item->ptr)
        {
          if (err)
            {
              g_warning ("Error loading image: %s", err->message);
              g_error_free (err);
            }

          if (created)
            mx_texture_cache_item_free (item);

          g_free (new_file);
          g_free (new_uri);

          return NULL;
        }

      if (created)
        add_texture_to_cache (self, uri, item);
    }

  g_free (new_file);
  g_free (new_uri);

  return item;
}
