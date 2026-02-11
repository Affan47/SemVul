__postconfig_schema_foreach(gpointer key, gpointer value, gpointer userdata)
{
	MgdSchemaTypeAttr *type_attr = (MgdSchemaTypeAttr *) value;
	MgdSchemaTypeAttr *parenttype = NULL;
	MidgardSchema *schema = (MidgardSchema *) userdata;
	gchar *typename = (gchar *) key;
	const gchar *parentname;

	parentname = type_attr->parent;

	if (parentname  != NULL ){


		if ((parenttype = midgard_schema_lookup_type(schema, (gchar *)parentname)) != NULL){

			if (!g_slist_find_custom(parenttype->children, (gpointer)typename, (GCompareFunc)g_strcmp0)) {
				parenttype->children =
					g_slist_append(parenttype->children, (gpointer) g_strdup(typename));
			}
		}
	}
}
