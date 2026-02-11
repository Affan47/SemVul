stl_style_property_get_color(const Style *stl, const gchar *property)
{
	StlProp	*pr;

	if((stl != NULL) && (property != NULL) && ((pr = g_hash_table_lookup(stl->properties, property)) != NULL))
	{
		if(pr->value->type == SPT_COLOR)
			return &pr->value->data.color;
	}
	return NULL;
}
