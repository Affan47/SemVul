my_xml_parse_file (const char *filename,
                   GError    **err)
{
  char *text;
  gsize length;
  xmlDocPtr doc;

  text = NULL;
  length = 0;

  if (!g_file_get_contents (filename,
                            &text,
                            &length,
                            err))
    return NULL;


  doc = xmlParseMemory (text, length);

  g_free (text);

  if (doc == NULL)
    {
      g_set_error (err,
                   GCONF_ERROR,
                   GCONF_ERROR_PARSE_ERROR,
                   _("Failed to parse XML file \"%s\""),
                   filename);
      return NULL;
    }

  return doc;
}
