RelationGetIndexExpressions(Relation relation)
{
	List	   *result;
	Datum		exprsDatum;
	bool		isnull;
	char	   *exprsString;
	MemoryContext oldcxt;


	if (relation->rd_indexprs)
		return (List *) copyObject(relation->rd_indexprs);


	if (relation->rd_indextuple == NULL ||
		heap_attisnull(relation->rd_indextuple, Anum_pg_index_indexprs))
		return NIL;


	exprsDatum = heap_getattr(relation->rd_indextuple,
							  Anum_pg_index_indexprs,
							  GetPgIndexDescriptor(),
							  &isnull);
	Assert(!isnull);
	exprsString = DatumGetCString(DirectFunctionCall1(textout, exprsDatum));
	result = (List *) stringToNode(exprsString);
	pfree(exprsString);


	result = (List *) eval_const_expressions(NULL, (Node *) result);


	set_coercionform_dontcare((Node *) result);


	fix_opfuncids((Node *) result);


	oldcxt = MemoryContextSwitchTo(relation->rd_indexcxt);
	relation->rd_indexprs = (List *) copyObject(result);
	MemoryContextSwitchTo(oldcxt);

	return result;
}
