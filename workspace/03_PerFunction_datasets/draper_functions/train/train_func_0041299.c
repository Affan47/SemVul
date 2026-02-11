__query_select_add_joins (MidgardQuerySelect *self, GdaSqlOperation *operation, GError **error)
{
	__add_implicit_workspace_join (self, operation);

	if (!MIDGARD_QUERY_EXECUTOR (self)->priv->joins)
		return TRUE;

	GSList *l = NULL;

	MidgardQueryExecutor *executor = MIDGARD_QUERY_EXECUTOR (self);
	GdaSqlStatement *sql_stm = executor->priv->stmt;
	GdaSqlStatementSelect *select = (GdaSqlStatementSelect *) sql_stm->contents;
	GdaSqlSelectFrom *from = select->from;
	GdaSqlSelectJoin *join;

	for (l = MIDGARD_QUERY_EXECUTOR (self)->priv->joins; l != NULL; l = l->next) {

		qsj *_sj = (qsj*) l->data;

		join = gda_sql_select_join_new (GDA_SQL_ANY_PART (from));
		join->type = _sj->join_type;

		MidgardQueryStorage *left_storage = _sj->left_property->priv->storage;
		MidgardQueryStorage *right_storage = _sj->right_property->priv->storage;

		GError *err = NULL;
		GValue lval = {0, };
		midgard_query_holder_get_value (MIDGARD_QUERY_HOLDER (_sj->left_property), &lval);
		gchar *left_table_field =
			midgard_core_query_compute_constraint_property (executor, left_storage, g_value_get_string (&lval), &err);
		if (err) {
			g_propagate_error (error, err);
			g_free (left_table_field);
		}

		GValue rval = {0, };
		midgard_query_holder_get_value (MIDGARD_QUERY_HOLDER (_sj->right_property), &rval);
		gchar *right_table_field =
			midgard_core_query_compute_constraint_property (executor, right_storage, g_value_get_string (&rval), &err);
		if (err) {
			g_propagate_error (error, err);
			g_free (right_table_field);
		}

		GdaSqlExpr *expr = gda_sql_expr_new (GDA_SQL_ANY_PART (join));
		expr->value = gda_value_new (G_TYPE_STRING);
		g_value_take_string (expr->value, g_strdup_printf ("%s = %s", left_table_field, right_table_field));

		join->expr = expr;
		join->position = ++executor->priv->joinid;


		MQE_SET_TABLE_ALIAS (executor, right_storage);
		gda_sql_select_from_take_new_join (from , join);
		GdaSqlSelectTarget *s_target = gda_sql_select_target_new (GDA_SQL_ANY_PART (from));
		s_target->table_name = g_strdup (right_storage->priv->table);
		s_target->as = g_strdup (right_storage->priv->table_alias);
		gda_sql_select_from_take_new_target (from, s_target);


		GdaSqlExpr *texpr = gda_sql_expr_new (GDA_SQL_ANY_PART (s_target));
		GValue *tval = g_new0 (GValue, 1);
		g_value_init (tval, G_TYPE_STRING);
		g_value_set_string (tval, right_storage->priv->table);
		texpr->value = tval;
		s_target->expr = texpr;
	}

	return TRUE;
}
