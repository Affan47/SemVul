gst_mpdparser_get_xml_prop_string (xmlNode * a_node,
    const gchar * property_name, gchar ** property_value)
{
  xmlChar *prop_string;
  gboolean exists = FALSE;

  prop_string = xmlGetProp (a_node, (const xmlChar *) property_name);
  if (prop_string) {
    *property_value = (gchar *) prop_string;
    exists = TRUE;
    GST_LOG (" - %s: %s", property_name, prop_string);
  }

  return exists;
}
