query_string_append_alias_list (coll_query_t *query, GString *qstring,
                                xmmsv_t *fields)
{
	coll_query_alias_t *alias;
	xmmsv_list_iter_t *it;
	xmmsv_t *valstr;
	gboolean first = TRUE;

	for (xmmsv_get_list_iter (fields, &it);
	     xmmsv_list_iter_valid (it);
	     xmmsv_list_iter_next (it)) {


		const gchar *field, *canon_field;
		xmmsv_list_iter_entry (it, &valstr);
		xmmsv_get_string (valstr, &field);
		canon_field = canonical_field_name (field);

		if (first) first = FALSE;
		else {
			g_string_append (qstring, ", ");
		}

		if (canon_field != NULL) {
			alias = query_get_alias (query, canon_field);
			if (alias != NULL) {
				query_string_append_alias (qstring, alias,
				                           COLL_QUERY_VALUE_TYPE_BOTH);
			} else {
				if (*field != '~') {
					if (strcmp(canon_field, "id") == 0) {
						g_string_append (qstring, "m0.id");
					} else {
						g_string_append_printf (qstring,
							"(SELECT IFNULL (intval, value) "
							 "FROM Media WHERE id = m0.id AND key='%s' AND "
							 "xmms_source_pref (source) = "
							  "(SELECT MIN (xmms_source_pref (n.source)) "
							   "FROM Media AS n WHERE n.id = m0.id AND "
							                         "n.key = '%s'))",
							canon_field, canon_field);
					}
				}
			}
		}


		if (*field == '-') {
			g_string_append (qstring, " DESC");
		} else if (*field == '~') {

			g_string_append (qstring, field + 1);
		}
	}
}
