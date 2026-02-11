_equalSubPlan(SubPlan *a, SubPlan *b)
{
	COMPARE_SCALAR_FIELD(subLinkType);
	COMPARE_NODE_FIELD(testexpr);
	COMPARE_NODE_FIELD(paramIds);
	COMPARE_SCALAR_FIELD(plan_id);
	COMPARE_SCALAR_FIELD(firstColType);
	COMPARE_SCALAR_FIELD(useHashTable);
	COMPARE_SCALAR_FIELD(unknownEqFalse);
	COMPARE_NODE_FIELD(setParam);
	COMPARE_NODE_FIELD(parParam);
	COMPARE_NODE_FIELD(args);

	return true;
}
