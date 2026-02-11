_equalMinMaxAggInfo(MinMaxAggInfo *a, MinMaxAggInfo *b)
{
	COMPARE_SCALAR_FIELD(aggfnoid);
	COMPARE_SCALAR_FIELD(aggsortop);
	COMPARE_NODE_FIELD(target);
	COMPARE_NODE_FIELD(pathkeys);

	return true;
}
