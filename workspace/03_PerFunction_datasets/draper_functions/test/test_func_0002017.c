e_xml_set_integer_prop_by_name (xmlNode *parent,
                                const xmlChar *prop_name,
                                gint value)
{
	gchar *valuestr;

	g_return_if_fail (parent != NULL);
	g_return_if_fail (prop_name != NULL);

	valuestr = g_strdup_printf ("%d", value);
	xmlSetProp (parent, prop_name, (guchar *) valuestr);
	g_free (valuestr);
}
