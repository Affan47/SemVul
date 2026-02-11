go_xml_node_get_enum (xmlNodePtr node, char const *name, GType etype, gint *val)
{
	GEnumClass *eclass = G_ENUM_CLASS (g_type_class_peek (etype));
	GEnumValue *ev;
	xmlChar *s;
	int i;

	s = xmlGetProp (node, CC2XML (name));
	if (s == NULL)
		return FALSE;

	ev = g_enum_get_value_by_name (eclass, CXML2C (s));
	if (!ev) ev = g_enum_get_value_by_nick (eclass, CXML2C (s));
	if (!ev && go_xml_node_get_int (node, name, &i))

		ev = g_enum_get_value (eclass, i);
	xmlFree (s);
	if (!ev) return FALSE;

	*val = ev->value;
	return TRUE;
}
