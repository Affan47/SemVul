stmt_rewrite_insert_remove (GdaSqlStatementInsert *ins, GdaSet *params, GError **error)
{
	if (!ins->values_list)

		return TRUE;

	if (ins->values_list->next) {
		TO_IMPLEMENT;
		g_set_error (error, GDA_SERVER_PROVIDER_ERROR,
			     GDA_SERVER_PROVIDER_DEFAULT_VALUE_HANDLING_ERROR,
			     "%s", "Not yet implemented");
		return FALSE;
	}

	GSList *fields, *values;
	for (fields = ins->fields_list, values = (GSList*) ins->values_list->data;
	     fields && values; ){
		GdaHolder *h;
		GdaSqlExpr *expr = (GdaSqlExpr*) values->data;
		if (! expr->param_spec || ! expr->param_spec->is_param) {
			fields = fields->next;
			values = values->next;
			continue;
		}
		h = gda_set_get_holder (params, expr->param_spec->name);
		if (!h) {
			gchar *str;
			str = g_strdup_printf (_("Missing parameter '%s' to execute query"),
					       expr->param_spec->name);
			g_set_error (error, GDA_SERVER_PROVIDER_ERROR,
				     GDA_SERVER_PROVIDER_MISSING_PARAM_ERROR,
				     "%s", str);
			g_free (str);
			return FALSE;
		}

		if (gda_holder_value_is_default (h)) {
			GSList *tmp;

			gda_sql_field_free ((GdaSqlField*) fields->data);
			tmp = fields->next;
			ins->fields_list = g_slist_delete_link (ins->fields_list, fields);
			fields = tmp;

			gda_sql_expr_free (expr);
			tmp = values->next;
			ins->values_list->data = g_slist_delete_link ((GSList*) ins->values_list->data,
								      values);
			values = tmp;
		}
		else {
			fields = fields->next;
			values = values->next;
		}
	}

	if (! ins->values_list->data) {
		g_slist_free (ins->values_list);
		ins->values_list = NULL;
	}

	return TRUE;
}
