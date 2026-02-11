midgard_quota_remove(MidgardObject *object, guint size){

	g_assert(object != NULL);

	MidgardConnection *mgd = MGD_OBJECT_CNC (object);

	if (!MGD_CNC_QUOTA (mgd) || !MGD_DBOBJECT_HAS_METADATA (object))
		return;

	GString *query;
	gchar *tmpstr;
	const gchar *typename = G_OBJECT_TYPE_NAME(object);


	query = g_string_new("UPDATE quota ");
	g_string_append_printf(query,
			"SET type_records=type_records-1"
			" WHERE typename='%s' AND type_records>0",
			typename);
	tmpstr = g_string_free(query, FALSE);
	midgard_core_query_execute(MGD_OBJECT_CNC (object), tmpstr, TRUE);
	g_free(tmpstr);

	query = g_string_new("UPDATE quota ");
	g_string_append_printf(query,
			"SET type_size=type_size-%d "
			"WHERE typename='%s' AND type_size>0",
			size, typename);

	tmpstr = g_string_free(query, FALSE);
	midgard_core_query_execute(MGD_OBJECT_CNC (object), tmpstr, TRUE);
	g_free(tmpstr);
}
