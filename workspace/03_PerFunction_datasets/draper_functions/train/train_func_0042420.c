parse_xml_file (MetaBuilder *builder,
		xmlDocPtr xml,
		char *dir)
{
  xmlNodePtr node;
  xmlChar *name;
  char *unescaped_name;
  MetaFile *dir_metafile, *metafile;

  dir_metafile =  meta_builder_lookup (builder, dir, TRUE);

  for (node = xml_get_root_children (xml);
       node != NULL; node = node->next)
    {
      if (strcmp ((char *)node->name, "file") == 0)
	{
	  name = xmlGetProp (node, (xmlChar *)"name");
	  unescaped_name = g_uri_unescape_string ((char *)name, "/");
	  xmlFree (name);

	  if (strcmp (unescaped_name, ".") == 0)
	    metafile = dir_metafile;
	  else
	    metafile = metafile_lookup_child (dir_metafile, unescaped_name, TRUE);

	  parse_xml_node (metafile, node);
	  g_free (unescaped_name);
	}
    }
}
