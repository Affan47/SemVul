get_photo (xmlNodePtr node)
{
  GHashTable *photo = g_hash_table_new_full (g_str_hash,
                                             g_str_equal,
                                             g_free,
                                             g_free);


  add_node (node, photo);


  node = node->xmlChildrenNode;

  while (node) {
    if (xmlStrcmp (node->name, (const xmlChar *) "owner") == 0 ||
        xmlStrcmp (node->name, (const xmlChar *) "dates") == 0) {
      add_node (node, photo);
    } else if (xmlStrcmp (node->name, (const xmlChar *) "title") == 0 ||
               xmlStrcmp (node->name, (const xmlChar *) "description") == 0) {
      g_hash_table_insert (photo,
                           g_strdup ((const gchar *) node->name),
                           (gchar *) xmlNodeGetContent (node));
    }

    node = node->next;
  }

  return photo;
}
