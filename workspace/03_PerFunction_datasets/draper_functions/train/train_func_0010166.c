_equalIndexStmt(IndexStmt *a, IndexStmt *b)
{
	COMPARE_STRING_FIELD(idxname);
	COMPARE_NODE_FIELD(relation);
	COMPARE_STRING_FIELD(accessMethod);
	COMPARE_STRING_FIELD(tableSpace);
	COMPARE_NODE_FIELD(indexParams);
	COMPARE_NODE_FIELD(options);
	COMPARE_NODE_FIELD(whereClause);
	COMPARE_NODE_FIELD(rangetable);
	COMPARE_SCALAR_FIELD(unique);
	COMPARE_SCALAR_FIELD(primary);
	COMPARE_SCALAR_FIELD(isconstraint);
	COMPARE_SCALAR_FIELD(concurrent);

	return true;
}
