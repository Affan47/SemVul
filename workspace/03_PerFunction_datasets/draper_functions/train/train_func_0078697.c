rest_xml_node_print (RestXmlNode *node)
{
  GHashTableIter iter;
  gpointer       key, value;
  char          *xml = g_strconcat ("<", node->name, NULL);
  RestXmlNode   *n;

  g_hash_table_iter_init (&iter, node->attrs);
  while (g_hash_table_iter_next (&iter, &key, &value))
    xml = g_strconcat (xml, " ", key, "=\'", value, "\'", NULL);

  xml = g_strconcat (xml, ">", NULL);

  g_hash_table_iter_init (&iter, node->children);
  while (g_hash_table_iter_next (&iter, &key, &value))
    {
      char *child = rest_xml_node_print ((RestXmlNode *) value);

      xml = g_strconcat (xml, child, NULL);
      g_free (child);
    }

  if (node->content)
    xml = g_strconcat (xml, node->content, "</", node->name, ">", NULL);
  else
    xml = g_strconcat (xml, "</", node->name, ">", NULL);

  for (n = node->next; n; n = n->next)
    {
      char *sibling = rest_xml_node_print (n);

      xml = g_strconcat (xml, sibling, NULL);
      g_free (sibling);
    }

  return xml;
}
