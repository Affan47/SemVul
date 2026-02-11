prefix_quals(Node *leftop, Oid opfamily,
			 Const *prefix_const, Pattern_Prefix_Status pstatus)
{
	List	   *result;
	Oid			datatype;
	Oid			oproid;
	Expr	   *expr;
	FmgrInfo	ltproc;
	Const	   *greaterstr;

	Assert(pstatus != Pattern_Prefix_None);

	switch (opfamily)
	{
		case TEXT_BTREE_FAM_OID:
		case TEXT_PATTERN_BTREE_FAM_OID:
			datatype = TEXTOID;
			break;

		case BPCHAR_BTREE_FAM_OID:
		case BPCHAR_PATTERN_BTREE_FAM_OID:
			datatype = BPCHAROID;
			break;

		case NAME_BTREE_FAM_OID:
		case NAME_PATTERN_BTREE_FAM_OID:
			datatype = NAMEOID;
			break;

		case BYTEA_BTREE_FAM_OID:
			datatype = BYTEAOID;
			break;

		default:

			elog(ERROR, "unexpected opfamily: %u", opfamily);
			return NIL;
	}


	if (prefix_const->consttype != datatype)
	{
		char	   *prefix;

		switch (prefix_const->consttype)
		{
			case TEXTOID:
				prefix = DatumGetCString(DirectFunctionCall1(textout,
												  prefix_const->constvalue));
				break;
			case BYTEAOID:
				prefix = DatumGetCString(DirectFunctionCall1(byteaout,
												  prefix_const->constvalue));
				break;
			default:
				elog(ERROR, "unexpected const type: %u",
					 prefix_const->consttype);
				return NIL;
		}
		prefix_const = string_to_const(prefix, datatype);
		pfree(prefix);
	}


	if (pstatus == Pattern_Prefix_Exact)
	{
		oproid = get_opfamily_member(opfamily, datatype, datatype,
									 BTEqualStrategyNumber);
		if (oproid == InvalidOid)
			elog(ERROR, "no = operator for opfamily %u", opfamily);
		expr = make_opclause(oproid, BOOLOID, false,
							 (Expr *) leftop, (Expr *) prefix_const);
		result = list_make1(make_simple_restrictinfo(expr));
		return result;
	}


	oproid = get_opfamily_member(opfamily, datatype, datatype,
								 BTGreaterEqualStrategyNumber);
	if (oproid == InvalidOid)
		elog(ERROR, "no >= operator for opfamily %u", opfamily);
	expr = make_opclause(oproid, BOOLOID, false,
						 (Expr *) leftop, (Expr *) prefix_const);
	result = list_make1(make_simple_restrictinfo(expr));


	oproid = get_opfamily_member(opfamily, datatype, datatype,
								 BTLessStrategyNumber);
	if (oproid == InvalidOid)
		elog(ERROR, "no < operator for opfamily %u", opfamily);
	fmgr_info(get_opcode(oproid), &ltproc);
	greaterstr = make_greater_string(prefix_const, &ltproc);
	if (greaterstr)
	{
		expr = make_opclause(oproid, BOOLOID, false,
							 (Expr *) leftop, (Expr *) greaterstr);
		result = lappend(result, make_simple_restrictinfo(expr));
	}

	return result;
}
