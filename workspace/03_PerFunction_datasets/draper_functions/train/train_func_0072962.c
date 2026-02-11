save_style(GNode *node, gpointer user)
{
	Style	*stl = node->data;
	FILE	*out = user;

	xml_put_node_open(out, "Style");
	xml_put_text(out, "name", stl->name);
	if(node->parent != NULL)
		xml_put_text(out, "parent", ((Style *) node->parent->data)->name);
	xml_put_boolean(out, "expand", stl->expand);
	if(stl_style_property_overrides(stl))
	{
		xml_put_node_open(out, "Properties");
		g_hash_table_foreach(stl->properties, save_property, out);
		xml_put_node_close(out, "Properties");
	}
	xml_put_node_close(out, "Style");

	return FALSE;
}
