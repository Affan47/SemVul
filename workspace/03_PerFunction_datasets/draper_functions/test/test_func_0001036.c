_copyMergeJoin(const MergeJoin *from)
{
	MergeJoin  *newnode = makeNode(MergeJoin);
	int			numCols;


	CopyJoinFields((const Join *) from, (Join *) newnode);


	COPY_NODE_FIELD(mergeclauses);
	numCols = list_length(from->mergeclauses);
	if (numCols > 0)
	{
		COPY_POINTER_FIELD(mergeFamilies, numCols * sizeof(Oid));
		COPY_POINTER_FIELD(mergeCollations, numCols * sizeof(Oid));
		COPY_POINTER_FIELD(mergeStrategies, numCols * sizeof(int));
		COPY_POINTER_FIELD(mergeNullsFirst, numCols * sizeof(bool));
	}

	return newnode;
}
