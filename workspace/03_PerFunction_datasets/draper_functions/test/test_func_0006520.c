default_render_distinct (GdaSqlStatementSelect *stmt, GdaSqlRenderingContext *context, GError **error)
{
	gboolean pretty = context->flags & GDA_STATEMENT_SQL_PRETTY;
	g_return_val_if_fail (stmt, NULL);
	g_return_val_if_fail (GDA_SQL_ANY_PART (stmt)->type == GDA_SQL_ANY_STMT_SELECT, NULL);

	if (stmt->distinct) {
		GString *string;
		string = g_string_new ("DISTINCT");
		if (stmt->distinct_expr) {
			gchar *str;
			str = context->render_expr (stmt->distinct_expr, context, NULL, NULL, error);
			if (!str) {
				g_string_free (string, TRUE);
				return NULL;
			}
			g_string_append (string, " ON (");
			g_string_append (string, str);
			g_string_append (string, ") ");
			g_free (str);
		}
		if (pretty)
			g_string_append_c (string, '\n');
		return g_string_free (string, FALSE);
	}
	else
		return NULL;
}
