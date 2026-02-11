left_oper(ParseState *pstate, List *op, Oid arg, bool noError, int location)
{
	Oid			operOid;
	OprCacheKey key;
	bool		key_ok;
	FuncDetailCode fdresult = FUNCDETAIL_NOTFOUND;
	HeapTuple	tup = NULL;


	key_ok = make_oper_cache_key(pstate, &key, op, InvalidOid, arg, location);

	if (key_ok)
	{
		operOid = find_oper_cache_entry(&key);
		if (OidIsValid(operOid))
		{
			tup = SearchSysCache1(OPEROID, ObjectIdGetDatum(operOid));
			if (HeapTupleIsValid(tup))
				return (Operator) tup;
		}
	}


	operOid = OpernameGetOprid(op, InvalidOid, arg);
	if (!OidIsValid(operOid))
	{


		FuncCandidateList clist;


		clist = OpernameGetCandidates(op, 'l', false);


		if (clist != NULL)
		{


			FuncCandidateList clisti;

			for (clisti = clist; clisti != NULL; clisti = clisti->next)
			{
				clisti->args[0] = clisti->args[1];
			}


			fdresult = oper_select_candidate(1, &arg, clist, &operOid);
		}
	}

	if (OidIsValid(operOid))
		tup = SearchSysCache1(OPEROID, ObjectIdGetDatum(operOid));

	if (HeapTupleIsValid(tup))
	{
		if (key_ok)
			make_oper_cache_entry(&key, operOid);
	}
	else if (!noError)
		op_error(pstate, op, 'l', InvalidOid, arg, fdresult, location);

	return (Operator) tup;
}
