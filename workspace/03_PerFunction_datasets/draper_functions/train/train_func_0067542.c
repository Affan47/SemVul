right_oper(ParseState *pstate, List *op, Oid arg, bool noError, int location)
{
	Oid			operOid;
	FuncDetailCode fdresult = FUNCDETAIL_NOTFOUND;
	HeapTuple	tup = NULL;


	operOid = OpernameGetOprid(op, arg, InvalidOid);
	if (!OidIsValid(operOid))
	{


		FuncCandidateList clist;


		clist = OpernameGetCandidates(op, 'r');


		if (clist != NULL)
		{


			fdresult = oper_select_candidate(1, &arg, clist, &operOid);
		}
	}

	if (OidIsValid(operOid))
		tup = SearchSysCache(OPEROID,
							 ObjectIdGetDatum(operOid),
							 0, 0, 0);

	if (!HeapTupleIsValid(tup) && !noError)
		op_error(pstate, op, 'r', arg, InvalidOid, fdresult, location);

	return (Operator) tup;
}
