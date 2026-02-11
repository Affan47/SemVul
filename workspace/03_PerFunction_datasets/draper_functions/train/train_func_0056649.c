load_style(const XmlNode *node, gpointer user)
{
	StyleInfo	*si = user;
	Style		*stl, *parent = NULL;
	const gchar	*name = "new style", *pname;
	const XmlNode	*prop;
	gboolean	btmp = FALSE;

	xml_get_text(node, "name", &name);
	stl = stl_style_new(name);

	if(xml_get_boolean(node, "expand", &btmp))
		stl_style_set_expand(stl, btmp);
	if((prop = xml_tree_search(node, "Properties")) != NULL)
		load_properties(prop, stl);
	if(xml_get_text(node, "parent", &pname))
		parent = stl_styleinfo_style_find(si, pname);
	stl_styleinfo_style_add(si, parent, stl);
}
