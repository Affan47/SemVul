gst_xml_parse_file (GstXML * xml, const guchar * fname, const guchar * root)
{
  xmlDocPtr doc;
  gboolean ret;

  g_return_val_if_fail (fname != NULL, FALSE);

  doc = xmlParseFile ((char *) fname);

  if (!doc) {
    g_warning ("gstxml: XML file \"%s\" could not be read\n", fname);
    return FALSE;
  }

  ret = gst_xml_parse_doc (xml, doc, root);

  xmlFreeDoc (doc);
  return ret;
}
