query_string_append_joins (gpointer key, gpointer val, gpointer udata)
{
	gchar *field;
	GString *qstring;
	coll_query_alias_t *alias;

	field = key;
	qstring = (GString*)udata;
	alias = (coll_query_alias_t*)val;

	if ((alias->id > 0) && (alias->type == XMMS_QUERY_ALIAS_PROP)) {
		if (alias->optional) {
			g_string_append_printf (qstring, " LEFT");
		}

		g_string_append_printf (qstring,
			" JOIN Media AS m%u ON m0.id=m%u.id AND m%u.key='%s' AND"
			" xmms_source_pref (m%u.source) = "
				"(SELECT MIN (xmms_source_pref (n.source)) FROM Media AS n"
				" WHERE n.id = m0.id AND n.key = '%s')",
			alias->id, alias->id, alias->id, field, alias->id, field);
	}
}
