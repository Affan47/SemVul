match_special_index_operator(Expr *clause, Oid opfamily, Oid idxcollation,
							 bool indexkey_on_left)
{
	bool		isIndexable = false;
	Node	   *rightop;
	Oid			expr_op;
	Oid			expr_coll;
	Const	   *patt;
	Const	   *prefix = NULL;
	Pattern_Prefix_Status pstatus = Pattern_Prefix_None;


	if (!indexkey_on_left)
		return false;


	rightop = get_rightop(clause);
	expr_op = ((OpExpr *) clause)->opno;
	expr_coll = ((OpExpr *) clause)->inputcollid;


	if (!IsA(rightop, Const) ||
		((Const *) rightop)->constisnull)
		return false;
	patt = (Const *) rightop;

	switch (expr_op)
	{
		case OID_TEXT_LIKE_OP:
		case OID_BPCHAR_LIKE_OP:
		case OID_NAME_LIKE_OP:

			pstatus = pattern_fixed_prefix(patt, Pattern_Type_Like, expr_coll,
										   &prefix, NULL);
			isIndexable = (pstatus != Pattern_Prefix_None);
			break;

		case OID_BYTEA_LIKE_OP:
			pstatus = pattern_fixed_prefix(patt, Pattern_Type_Like, expr_coll,
										   &prefix, NULL);
			isIndexable = (pstatus != Pattern_Prefix_None);
			break;

		case OID_TEXT_ICLIKE_OP:
		case OID_BPCHAR_ICLIKE_OP:
		case OID_NAME_ICLIKE_OP:

			pstatus = pattern_fixed_prefix(patt, Pattern_Type_Like_IC, expr_coll,
										   &prefix, NULL);
			isIndexable = (pstatus != Pattern_Prefix_None);
			break;

		case OID_TEXT_REGEXEQ_OP:
		case OID_BPCHAR_REGEXEQ_OP:
		case OID_NAME_REGEXEQ_OP:

			pstatus = pattern_fixed_prefix(patt, Pattern_Type_Regex, expr_coll,
										   &prefix, NULL);
			isIndexable = (pstatus != Pattern_Prefix_None);
			break;

		case OID_TEXT_ICREGEXEQ_OP:
		case OID_BPCHAR_ICREGEXEQ_OP:
		case OID_NAME_ICREGEXEQ_OP:

			pstatus = pattern_fixed_prefix(patt, Pattern_Type_Regex_IC, expr_coll,
										   &prefix, NULL);
			isIndexable = (pstatus != Pattern_Prefix_None);
			break;

		case OID_INET_SUB_OP:
		case OID_INET_SUBEQ_OP:
			isIndexable = true;
			break;
	}

	if (prefix)
	{
		pfree(DatumGetPointer(prefix->constvalue));
		pfree(prefix);
	}


	if (!isIndexable)
		return false;


	switch (expr_op)
	{
		case OID_TEXT_LIKE_OP:
		case OID_TEXT_ICLIKE_OP:
		case OID_TEXT_REGEXEQ_OP:
		case OID_TEXT_ICREGEXEQ_OP:
			isIndexable =
				(opfamily == TEXT_PATTERN_BTREE_FAM_OID) ||
				(opfamily == TEXT_SPGIST_FAM_OID) ||
				(opfamily == TEXT_BTREE_FAM_OID &&
				 (pstatus == Pattern_Prefix_Exact ||
				  lc_collate_is_c(idxcollation)));
			break;

		case OID_BPCHAR_LIKE_OP:
		case OID_BPCHAR_ICLIKE_OP:
		case OID_BPCHAR_REGEXEQ_OP:
		case OID_BPCHAR_ICREGEXEQ_OP:
			isIndexable =
				(opfamily == BPCHAR_PATTERN_BTREE_FAM_OID) ||
				(opfamily == BPCHAR_BTREE_FAM_OID &&
				 (pstatus == Pattern_Prefix_Exact ||
				  lc_collate_is_c(idxcollation)));
			break;

		case OID_NAME_LIKE_OP:
		case OID_NAME_ICLIKE_OP:
		case OID_NAME_REGEXEQ_OP:
		case OID_NAME_ICREGEXEQ_OP:

			isIndexable = (opfamily == NAME_BTREE_FAM_OID);
			break;

		case OID_BYTEA_LIKE_OP:
			isIndexable = (opfamily == BYTEA_BTREE_FAM_OID);
			break;

		case OID_INET_SUB_OP:
		case OID_INET_SUBEQ_OP:
			isIndexable = (opfamily == NETWORK_BTREE_FAM_OID);
			break;
	}

	return isIndexable;
}
