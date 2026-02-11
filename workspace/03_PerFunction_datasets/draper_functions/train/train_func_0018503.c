visu_config_file_addFloatArrayEntry(int kind, const gchar *key,
                                                         const gchar* description,
                                                         guint nValues, float *location,
                                                         float clamp[2])
{
  VisuConfigFileEntry *entry;

  g_return_val_if_fail(location, (VisuConfigFileEntry*)0);

  entry = entry_init(key, description, kind, 1);
  if (!entry)
    return (VisuConfigFileEntry*)0;
  entry->read = _readFloatv;
  entry->storage = (gpointer)location;
  entry->nValues = nValues;
  entry->range[0] = clamp[0];
  entry->range[1] = clamp[1];

  if (!entry_register(entry))
    {
      g_free(entry);
      g_warning("entry '%s' already exists!", key);
    }

  return entry;
}
