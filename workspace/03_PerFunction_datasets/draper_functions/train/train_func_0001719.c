_midgard_view_derived_delete_storage(MidgardConnection *mgd, MidgardDBObjectClass *klass)
{
	g_return_val_if_fail(mgd != NULL, FALSE);
	g_return_val_if_fail(klass != NULL, FALSE);

	MgdSchemaTypeAttr *type_attr = midgard_core_class_get_type_attr(klass);


	GString *query = g_string_new("DROP VIEW ");
	g_string_append(query, type_attr->name);

	gint rv = midgard_core_query_execute(mgd, query->str, FALSE);

	g_string_free(query, TRUE);

	if (rv == -1)
		return FALSE;

	return TRUE;
}
