clutter_path_add_string (ClutterPath *path,
                         const gchar *str)
{
  GSList *nodes;

  g_return_val_if_fail (CLUTTER_IS_PATH (path), FALSE);
  g_return_val_if_fail (str != NULL, FALSE);

  if (clutter_path_parse_description (str, &nodes))
    {
      clutter_path_add_nodes (path, nodes);

      return TRUE;
    }
  else
    return FALSE;
}
