_copyAgg(const Agg *from)
{
	Agg		   *newnode = makeNode(Agg);

	CopyPlanFields((const Plan *) from, (Plan *) newnode);

	COPY_SCALAR_FIELD(aggstrategy);
	COPY_SCALAR_FIELD(numCols);
	if (from->numCols > 0)
	{
		COPY_POINTER_FIELD(grpColIdx, from->numCols * sizeof(AttrNumber));
		COPY_POINTER_FIELD(grpOperators, from->numCols * sizeof(Oid));
	}
	COPY_SCALAR_FIELD(numGroups);
	COPY_NODE_FIELD(groupingSets);
	COPY_NODE_FIELD(chain);

	return newnode;
}
