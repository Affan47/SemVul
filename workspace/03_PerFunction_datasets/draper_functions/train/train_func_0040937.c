glade_xml_get_property_version (GladeXmlNode * node_in,
                                const gchar * name,
                                guint16 * major, guint16 * minor)
{
  xmlNodePtr node = (xmlNodePtr) node_in;
  gchar *value = glade_xml_get_property_string (node_in, name);
  gchar **split;

  if (!value)
    return FALSE;

  if ((split = g_strsplit (value, ".", 2)))
    {
      if (!split[0] || !split[1])
        {
          g_warning ("Malformed version property \"%s\"\n"
                     "Under the \"%s\" tag (%s)", name, node->name, value);
          return FALSE;
        }

      *major = g_ascii_strtoll (split[0], NULL, 10);
      *minor = g_ascii_strtoll (split[1], NULL, 10);

      g_strfreev (split);
    }

  g_free (value);

  return TRUE;
}
