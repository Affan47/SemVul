EvaluateParams(PreparedStatement *pstmt, List *params,
			   const char *queryString, EState *estate)
{
	Oid		   *param_types = pstmt->plansource->param_types;
	int			num_params = pstmt->plansource->num_params;
	int			nparams = list_length(params);
	ParseState *pstate;
	ParamListInfo paramLI;
	List	   *exprstates;
	ListCell   *l;
	int			i;

	if (nparams != num_params)
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
		   errmsg("wrong number of parameters for prepared statement \"%s\"",
				  pstmt->stmt_name),
				 errdetail("Expected %d parameters but got %d.",
						   num_params, nparams)));


	if (num_params == 0)
		return NULL;


	params = (List *) copyObject(params);

	pstate = make_parsestate(NULL);
	pstate->p_sourcetext = queryString;

	i = 0;
	foreach(l, params)
	{
		Node	   *expr = lfirst(l);
		Oid			expected_type_id = param_types[i];
		Oid			given_type_id;

		expr = transformExpr(pstate, expr);


		if (pstate->p_hasSubLinks)
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("cannot use subquery in EXECUTE parameter")));
		if (pstate->p_hasAggs)
			ereport(ERROR,
					(errcode(ERRCODE_GROUPING_ERROR),
			  errmsg("cannot use aggregate function in EXECUTE parameter")));
		if (pstate->p_hasWindowFuncs)
			ereport(ERROR,
					(errcode(ERRCODE_WINDOWING_ERROR),
				 errmsg("cannot use window function in EXECUTE parameter")));

		given_type_id = exprType(expr);

		expr = coerce_to_target_type(pstate, expr, given_type_id,
									 expected_type_id, -1,
									 COERCION_ASSIGNMENT,
									 COERCE_IMPLICIT_CAST,
									 -1);

		if (expr == NULL)
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("parameter $%d of type %s cannot be coerced to the expected type %s",
							i + 1,
							format_type_be(given_type_id),
							format_type_be(expected_type_id)),
			   errhint("You will need to rewrite or cast the expression.")));

		lfirst(l) = expr;
		i++;
	}


	exprstates = (List *) ExecPrepareExpr((Expr *) params, estate);


	paramLI = (ParamListInfo)
		palloc(sizeof(ParamListInfoData) +
			   (num_params - 1) *sizeof(ParamExternData));

	paramLI->paramFetch = NULL;
	paramLI->paramFetchArg = NULL;
	paramLI->parserSetup = NULL;
	paramLI->parserSetupArg = NULL;
	paramLI->numParams = num_params;

	i = 0;
	foreach(l, exprstates)
	{
		ExprState  *n = lfirst(l);
		ParamExternData *prm = &paramLI->params[i];

		prm->ptype = param_types[i];
		prm->pflags = 0;
		prm->value = ExecEvalExprSwitchContext(n,
											   GetPerTupleExprContext(estate),
											   &prm->isnull,
											   NULL);

		i++;
	}

	return paramLI;
}
