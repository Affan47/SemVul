__get_tdata_foreach(gpointer key, gpointer value, gpointer user_data)
{
	MgdSchemaTypeAttr *type_attr = (MgdSchemaTypeAttr *) value;
	guint np;

	if(g_type_from_name(key))
		return;

	np = g_hash_table_size(type_attr->prophash);
	if (np < 1)
		return;

	if (type_attr->table)
		g_hash_table_foreach(type_attr->prophash, __get_pdata_foreach, type_attr);
}
