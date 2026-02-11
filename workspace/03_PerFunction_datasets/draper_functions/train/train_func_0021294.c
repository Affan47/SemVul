remove_thumbnailer (GnomeDesktopThumbnailFactory *factory,
                    const gchar                  *path)
{
  GnomeDesktopThumbnailFactoryPrivate *priv = factory->priv;
  GList *l;
  Thumbnailer *thumb;

  g_mutex_lock (&priv->lock);

  for (l = priv->thumbnailers; l; l = g_list_next (l))
    {
      thumb = (Thumbnailer *)l->data;

      if (strcmp (thumb->path, path) == 0)
        {
          priv->thumbnailers = g_list_delete_link (priv->thumbnailers, l);
          g_hash_table_foreach_remove (priv->mime_types_map,
                                       (GHRFunc)remove_thumbnailer_from_mime_type_map,
                                       (gpointer)path);
          thumbnailer_unref (thumb);

          break;
        }
    }

  g_mutex_unlock (&priv->lock);
}
