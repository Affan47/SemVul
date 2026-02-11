e_xml_set_bool_prop_by_name (xmlNode *parent,
                             const xmlChar *prop_name,
                             gboolean value)
{
	g_return_if_fail (parent != NULL);
	g_return_if_fail (prop_name != NULL);

	if (value) {
		xmlSetProp (parent, prop_name, (const guchar *)"true");
	} else {
		xmlSetProp (parent, prop_name, (const guchar *)"false");
	}
}
