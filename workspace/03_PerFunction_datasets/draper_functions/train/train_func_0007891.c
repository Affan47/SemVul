finalize (GObject *object)
{
  GeglTileBackendTileDir *self = (GeglTileBackendTileDir *) object;
  GFileEnumerator *enumerator;
  GFileInfo       *info;

  enumerator = g_file_enumerate_children (self->buffer_dir, "standard::*",
                          G_FILE_QUERY_INFO_NONE, NULL, NULL);

  for (info = g_file_enumerator_next_file (enumerator, NULL, NULL);
       info;
       info = g_file_enumerator_next_file (enumerator, NULL, NULL))
    {
      const gchar *name = g_file_info_get_name (info);
      if (name)
        {
          GFile *file = g_file_get_child (self->buffer_dir, name);
          if (file)
            {
              g_file_delete (file, NULL, NULL);
              g_object_unref (file);
            }
        }
      g_object_unref (info);
    }

  g_object_unref (enumerator);

  g_file_delete (self->buffer_dir, NULL, NULL);
  g_object_unref (self->buffer_dir);

  (*G_OBJECT_CLASS (parent_class)->finalize)(object);
}
