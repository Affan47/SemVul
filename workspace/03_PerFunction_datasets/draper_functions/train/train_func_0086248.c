expand_indexqual_opclause(RestrictInfo *rinfo, Oid opfamily)
{
	Expr	   *clause = rinfo->clause;


	Node	   *leftop = get_leftop(clause);
	Node	   *rightop = get_rightop(clause);
	Oid			expr_op = ((OpExpr *) clause)->opno;
	Const	   *patt = (Const *) rightop;
	Const	   *prefix = NULL;
	Const	   *rest = NULL;
	Pattern_Prefix_Status pstatus;
	List	   *result;

	switch (expr_op)
	{


		case OID_TEXT_LIKE_OP:
		case OID_BPCHAR_LIKE_OP:
		case OID_NAME_LIKE_OP:
		case OID_BYTEA_LIKE_OP:
			pstatus = pattern_fixed_prefix(patt, Pattern_Type_Like,
										   &prefix, &rest);
			result = prefix_quals(leftop, opfamily, prefix, pstatus);
			break;

		case OID_TEXT_ICLIKE_OP:
		case OID_BPCHAR_ICLIKE_OP:
		case OID_NAME_ICLIKE_OP:

			pstatus = pattern_fixed_prefix(patt, Pattern_Type_Like_IC,
										   &prefix, &rest);
			result = prefix_quals(leftop, opfamily, prefix, pstatus);
			break;

		case OID_TEXT_REGEXEQ_OP:
		case OID_BPCHAR_REGEXEQ_OP:
		case OID_NAME_REGEXEQ_OP:

			pstatus = pattern_fixed_prefix(patt, Pattern_Type_Regex,
										   &prefix, &rest);
			result = prefix_quals(leftop, opfamily, prefix, pstatus);
			break;

		case OID_TEXT_ICREGEXEQ_OP:
		case OID_BPCHAR_ICREGEXEQ_OP:
		case OID_NAME_ICREGEXEQ_OP:

			pstatus = pattern_fixed_prefix(patt, Pattern_Type_Regex_IC,
										   &prefix, &rest);
			result = prefix_quals(leftop, opfamily, prefix, pstatus);
			break;

		case OID_INET_SUB_OP:
		case OID_INET_SUBEQ_OP:
			result = network_prefix_quals(leftop, expr_op, opfamily,
										  patt->constvalue);
			break;

		default:
			result = list_make1(rinfo);
			break;
	}

	return result;
}
