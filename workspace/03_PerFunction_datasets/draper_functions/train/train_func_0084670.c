_readBoolean(VisuConfigFileEntry *entry, gchar **lines, int nbLines,
                             int position, VisuData *dataObj _U_,
                             VisuGlView *view _U_, GError **error)
{
  gboolean val;

  g_return_val_if_fail(nbLines == 1 && entry->storage, FALSE);

  if (!tool_config_file_readBoolean(lines[0], position, &val, 1, error))
    return FALSE;
  *((gboolean*)entry->storage) = val;
  return TRUE;
}
