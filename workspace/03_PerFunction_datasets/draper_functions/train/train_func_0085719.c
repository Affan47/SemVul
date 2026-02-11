parse_children (ObjectInfo *oinfo,
                JsonNode   *node)
{
  JsonArray *array;
  GList *retval;
  guint array_len, i;

  if (JSON_NODE_TYPE (node) != JSON_NODE_ARRAY)
    return NULL;

  retval = oinfo->children;

  array = json_node_get_array (node);
  array_len = json_array_get_length (array);

  for (i = 0; i < array_len; i++)
    {
      JsonNode *child = json_array_get_element (array, i);
      const gchar *id_;

      id_ = _clutter_script_get_id_from_node (child);
      if (id_ != NULL)
        retval = g_list_prepend (retval, g_strdup (id_));
    }

  return g_list_reverse (retval);
}
