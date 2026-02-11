match_agg_to_index_col(MinMaxAggInfo *info, IndexOptInfo *index, int indexcol)
{
	int			strategy;


	if (!match_index_to_operand((Node *) info->target, indexcol, index))
		return NoMovementScanDirection;


	strategy = get_op_opclass_strategy(info->aggsortop,
									   index->classlist[indexcol]);
	if (strategy == BTLessStrategyNumber)
		return ForwardScanDirection;
	if (strategy == BTGreaterStrategyNumber)
		return BackwardScanDirection;
	return NoMovementScanDirection;
}
