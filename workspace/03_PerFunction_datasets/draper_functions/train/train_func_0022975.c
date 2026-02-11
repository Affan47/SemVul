rest_xml_node_find (RestXmlNode *start,
                    const gchar *tag)
{
  RestXmlNode *node;
  RestXmlNode *tmp;
  GQueue stack = G_QUEUE_INIT;
  GList *children, *l;
  const char *tag_interned;

  g_return_val_if_fail (start, NULL);
  g_return_val_if_fail (start->ref_count > 0, NULL);

  tag_interned = g_intern_string (tag);

  g_queue_push_head (&stack, start);

  while ((node = g_queue_pop_head (&stack)) != NULL)
  {
    if ((tmp = g_hash_table_lookup (node->children, tag_interned)) != NULL)
    {
      g_queue_clear (&stack);
      return tmp;
    }

    children = g_hash_table_get_values (node->children);
    for (l = children; l; l = l->next)
    {
      g_queue_push_head (&stack, l->data);
    }
    g_list_free (children);
  }

  g_queue_clear (&stack);
  return NULL;
}
