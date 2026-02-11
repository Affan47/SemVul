free_if(PLpgSQL_stmt_if *stmt)
{
	ListCell   *l;

	free_expr(stmt->cond);
	free_stmts(stmt->then_body);
	foreach(l, stmt->elsif_list)
	{
		PLpgSQL_if_elsif *elif = (PLpgSQL_if_elsif *) lfirst(l);

		free_expr(elif->cond);
		free_stmts(elif->stmts);
	}
	free_stmts(stmt->else_body);
}
