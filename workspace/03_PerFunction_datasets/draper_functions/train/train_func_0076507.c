ExecEvalWholeRowSlow(ExprState *exprstate, ExprContext *econtext,
					 bool *isNull, ExprDoneCond *isDone)
{
	Var		   *variable = (Var *) exprstate->expr;
	TupleTableSlot *slot = econtext->ecxt_scantuple;
	HeapTuple	tuple;
	TupleDesc	var_tupdesc;
	HeapTupleHeader dtuple;

	if (isDone)
		*isDone = ExprSingleResult;
	*isNull = false;


	Assert(variable->vartype != RECORDOID);
	var_tupdesc = lookup_rowtype_tupdesc(variable->vartype, -1);

	tuple = ExecFetchSlotTuple(slot);


	dtuple = (HeapTupleHeader) palloc(tuple->t_len);
	memcpy((char *) dtuple, (char *) tuple->t_data, tuple->t_len);

	HeapTupleHeaderSetDatumLength(dtuple, tuple->t_len);
	HeapTupleHeaderSetTypeId(dtuple, variable->vartype);
	HeapTupleHeaderSetTypMod(dtuple, variable->vartypmod);

	Assert(HeapTupleHeaderGetNatts(dtuple) >= var_tupdesc->natts);
	HeapTupleHeaderSetNatts(dtuple, var_tupdesc->natts);

	ReleaseTupleDesc(var_tupdesc);

	return PointerGetDatum(dtuple);
}
