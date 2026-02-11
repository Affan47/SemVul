command_gda_report_if (GdaReportEngine *engine, xmlNodePtr node, GSList **created_nodes,
		       RunContext *context, GError **error)
{
	GValue *value;
	gboolean expr_is_true = FALSE;
	xmlChar *prop;

	prop = xmlGetProp (node, BAD_CAST "expr");
	if (!prop) {
		g_set_error (error, 0, 0, "%s",
			     _("No expression specified"));
		return FALSE;
	}


	value = evaluate_expression (engine, context,
				     (const gchar *) prop, error);
	if (!value)
		return FALSE;
	xmlFree (prop);
	if (value && !gda_value_is_null (value)) {
		if (G_VALUE_TYPE (value) == G_TYPE_BOOLEAN)
			expr_is_true = g_value_get_boolean (value);
		else {
			GValue *trans;
			trans = gda_value_new (G_TYPE_BOOLEAN);
			if (g_value_transform (value, trans)) {
				expr_is_true = g_value_get_boolean (trans);
				gda_value_free (trans);
			}
			else {
				gda_value_free (trans);
				g_set_error (error, 0, 0,
					     _("Cannot cast value from type '%s' to type '%s'"),
					     g_type_name (G_VALUE_TYPE (value)), g_type_name (G_TYPE_BOOLEAN));
				return FALSE;
			}
		}
		gda_value_free (value);
	}


	gchar *sub_node_name;
	xmlNodePtr sub_node;
	sub_node_name = expr_is_true ? "gda_report_if_true" : "gda_report_if_false";
	for (sub_node = node->children; sub_node; sub_node = sub_node->next) {
		if (!strcmp ((gchar *) sub_node->name, sub_node_name)) {
			if (!real_run_at_node (engine, sub_node->children, context, error))
				return FALSE;
			else {
				xmlNodePtr child;
				for (child = sub_node->children; child; child = sub_node->children) {
					xmlUnlinkNode (child);
					*created_nodes = g_slist_prepend (*created_nodes, child);
				}
			}
		}
	}

	*created_nodes = g_slist_reverse (*created_nodes);

	return TRUE;
}
