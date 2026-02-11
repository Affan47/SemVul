cc_background_xml_get_bool (const xmlNode *parent,
			    const gchar   *prop_name)
{
  xmlChar * prop;
  gboolean ret_val = FALSE;

  g_return_val_if_fail (parent != NULL, FALSE);
  g_return_val_if_fail (prop_name != NULL, FALSE);

  prop = xmlGetProp ((xmlNode *) parent, (xmlChar*)prop_name);
  if (prop != NULL) {
    if (!g_ascii_strcasecmp ((gchar *)prop, "true") || !g_ascii_strcasecmp ((gchar *)prop, "1")) {
      ret_val = TRUE;
    } else {
      ret_val = FALSE;
    }
    g_free (prop);
  }

  return ret_val;
}
