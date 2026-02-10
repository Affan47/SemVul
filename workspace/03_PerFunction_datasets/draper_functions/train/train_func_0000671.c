exec_simple_check_plan(PLpgSQL_expr *expr)
{
	_SPI_plan  *spi_plan = (_SPI_plan *) expr->plan;
	Plan	   *plan;
	TargetEntry *tle;

	expr->expr_simple_expr = NULL;


	if (list_length(spi_plan->ptlist) != 1)
		return;

	plan = (Plan *) linitial(spi_plan->ptlist);


	if (plan == NULL)
		return;

	if (!IsA(plan, Result))
		return;


	if (plan->lefttree != NULL ||
		plan->righttree != NULL ||
		plan->initPlan != NULL ||
		plan->qual != NULL ||
		((Result *) plan)->resconstantqual != NULL)
		return;


	if (list_length(plan->targetlist) != 1)
		return;

	tle = (TargetEntry *) linitial(plan->targetlist);


	if (!exec_simple_check_node((Node *) tle->expr))
		return;


	expr->expr_simple_expr = tle->expr;
	expr->expr_simple_state = NULL;
	expr->expr_simple_in_use = false;
	expr->expr_simple_id = -1;

	expr->expr_simple_type = exprType((Node *) tle->expr);
}
