__add_exclude_deleted_constraints (MidgardQueryExecutor *self, GdaSqlStatementSelect *select, GdaSqlOperation *operation, MidgardDBObjectClass *dbklass)
{
	GSList *l = select->from->targets;
	const gchar *deleted_field = midgard_core_object_get_deleted_field (dbklass);
	gboolean bool_is_int = MIDGARD_QUERY_EXECUTOR (self)->priv->bool_is_int;


	if (g_slist_length (l) == 1) {

		if (!deleted_field)
			return;

		GdaSqlSelectTarget *target = (GdaSqlSelectTarget *) l->data;
		GdaSqlExpr *expr = gda_sql_expr_new (GDA_SQL_ANY_PART (operation));
		expr->value = gda_value_new (G_TYPE_STRING);
		g_value_take_string (expr->value, g_strdup_printf ("%s.%s = %s", target->as, deleted_field, __BOOL_VALUE (bool_is_int)));
		operation->operands = g_slist_append (operation->operands, expr);

		return;
	}


 	GdaSqlExpr *deleted_expr = gda_sql_expr_new (GDA_SQL_ANY_PART (operation));
	GdaSqlOperation *deleted_operation = gda_sql_operation_new (GDA_SQL_ANY_PART (deleted_expr));
	deleted_operation->operator_type = GDA_SQL_OPERATOR_TYPE_AND;
	deleted_expr->cond = deleted_operation;
	operation->operands = g_slist_append (operation->operands, deleted_expr);


	for (l = select->from->targets; l != NULL; l = l->next) {
		GdaSqlSelectTarget *target = (GdaSqlSelectTarget *) l->data;
		GdaSqlExpr *expr = gda_sql_expr_new (GDA_SQL_ANY_PART (operation));
        	expr->value = gda_value_new (G_TYPE_STRING);
        	g_value_take_string (expr->value, g_strdup_printf ("%s.metadata_deleted = %s", target->as, __BOOL_VALUE (bool_is_int)));
        	deleted_operation->operands = g_slist_append (deleted_operation->operands, expr);
	}
}
