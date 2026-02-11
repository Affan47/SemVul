read_colorscheme (gchar * fileName, GList ** list)
{
  xmlDocPtr doc;
  xmlNodePtr node;
  colorschemed *scheme = NULL;

  if (!file_is_readable (fileName)
      && !(strncmp ("http", fileName, 4) == 0
           || strncmp ("ftp", fileName, 3) == 0)) {
    fprintf (stderr, "Couldn't read colorscheme from %s\n", fileName);
    fflush (stderr);
    return (NULL);
  }


  doc = xmlParseFile (fileName);
  if (doc == NULL)
    return (NULL);


  node = xmlDocGetRootElement (doc);
  if (strcmp ((char *) node->name, "colormap") == 0) {
    scheme = process_colorscheme (node, doc);
    if (list) {
      *list = g_list_append (*list, scheme);
    }
    return (scheme);
  }

  node = XML_CHILDREN (node);
  while (node) {
    if (node->type != XML_TEXT_NODE && node->type != XML_COMMENT_NODE) {
      scheme = process_colorscheme (node, doc);
      if (list)
        *list = g_list_append (*list, scheme);
    }

    node = node->next;
  }
  xmlFreeDoc (doc);

  if (sessionOptions->verbose == GGOBI_VERBOSE)
    g_printerr ("Read colorscheme from %s\n", fileName);

  return (scheme);
}
