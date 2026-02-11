gda_sql_select_target_take_select (GdaSqlSelectTarget *target, GdaSqlStatement *stmt)
{
	if (stmt) {
		target->expr = gda_sql_expr_new (GDA_SQL_ANY_PART (target));
		gda_sql_expr_take_select (target->expr, stmt);
	}
}
