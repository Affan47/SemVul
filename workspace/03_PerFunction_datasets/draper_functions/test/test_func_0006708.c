gnome_desktop_thumbnail_factory_is_disabled (GnomeDesktopThumbnailFactory *factory,
                                             const gchar                  *mime_type)
{
  GnomeDesktopThumbnailFactoryPrivate *priv = factory->priv;
  guint i;

  if (priv->disabled)
    return TRUE;

  if (!priv->disabled_types)
    return FALSE;

  for (i = 0; priv->disabled_types[i]; i++)
    {
      if (g_strcmp0 (priv->disabled_types[i], mime_type) == 0)
        return TRUE;
    }

  return FALSE;
}
