param_to_null_foreach (GdaSqlAnyPart *part, G_GNUC_UNUSED gpointer data, G_GNUC_UNUSED GError **error)
{
	if (part->type == GDA_SQL_ANY_EXPR) {
		GdaSqlExpr *expr = (GdaSqlExpr*) part;
		if (expr->param_spec) {
			GType type = expr->param_spec->g_type;
			gda_sql_param_spec_free (expr->param_spec);
			expr->param_spec = NULL;

			if (!expr->value) {
				if (type != GDA_TYPE_NULL)
					expr->value = gda_value_new_from_string ("0", type);
				else
					g_value_set_int ((expr->value = gda_value_new (G_TYPE_INT)), 0);
			}
		}
	}
	return TRUE;
}
