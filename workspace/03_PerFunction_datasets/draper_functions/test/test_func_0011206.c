RelationGetIndexPredicate(Relation relation)
{
	List	   *result;
	Datum		predDatum;
	bool		isnull;
	char	   *predString;
	MemoryContext oldcxt;


	if (relation->rd_indpred)
		return (List *) copyObject(relation->rd_indpred);


	if (relation->rd_indextuple == NULL ||
		heap_attisnull(relation->rd_indextuple, Anum_pg_index_indpred))
		return NIL;


	predDatum = heap_getattr(relation->rd_indextuple,
							 Anum_pg_index_indpred,
							 GetPgIndexDescriptor(),
							 &isnull);
	Assert(!isnull);
	predString = TextDatumGetCString(predDatum);
	result = (List *) stringToNode(predString);
	pfree(predString);


	result = (List *) eval_const_expressions(NULL, (Node *) result);

	result = (List *) canonicalize_qual((Expr *) result);


	result = make_ands_implicit((Expr *) result);


	fix_opfuncids((Node *) result);


	oldcxt = MemoryContextSwitchTo(relation->rd_indexcxt);
	relation->rd_indpred = (List *) copyObject(result);
	MemoryContextSwitchTo(oldcxt);

	return result;
}
