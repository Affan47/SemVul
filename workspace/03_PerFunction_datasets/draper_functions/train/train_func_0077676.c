add_sort_column(AttrNumber colIdx, Oid sortOp, Oid coll, bool nulls_first,
				int numCols, AttrNumber *sortColIdx,
				Oid *sortOperators, Oid *collations, bool *nullsFirst)
{
	int			i;

	Assert(OidIsValid(sortOp));

	for (i = 0; i < numCols; i++)
	{


		if (sortColIdx[i] == colIdx &&
			sortOperators[numCols] == sortOp &&
			collations[numCols] == coll)
		{

			return numCols;
		}
	}


	sortColIdx[numCols] = colIdx;
	sortOperators[numCols] = sortOp;
	collations[numCols] = coll;
	nullsFirst[numCols] = nulls_first;
	return numCols + 1;
}
