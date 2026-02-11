planner(Query *parse, int cursorOptions, ParamListInfo boundParams)
{
	PlannedStmt *result;

	if (planner_hook)
		result = (*planner_hook) (parse, cursorOptions, boundParams);
	else
		result = standard_planner(parse, cursorOptions, boundParams);
	return result;
}
