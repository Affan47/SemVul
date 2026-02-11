ComputeIndexAttrs(IndexInfo *indexInfo,
				  Oid *classOidP,
				  List *attList,
				  Oid relId,
				  char *accessMethodName,
				  Oid accessMethodId,
				  bool isconstraint)
{
	ListCell   *rest;
	int			attn = 0;


	foreach(rest, attList)
	{
		IndexElem  *attribute = (IndexElem *) lfirst(rest);
		Oid			atttype;

		if (attribute->name != NULL)
		{

			HeapTuple	atttuple;
			Form_pg_attribute attform;

			Assert(attribute->expr == NULL);
			atttuple = SearchSysCacheAttName(relId, attribute->name);
			if (!HeapTupleIsValid(atttuple))
			{

				if (isconstraint)
					ereport(ERROR,
							(errcode(ERRCODE_UNDEFINED_COLUMN),
						  errmsg("column \"%s\" named in key does not exist",
								 attribute->name)));
				else
					ereport(ERROR,
							(errcode(ERRCODE_UNDEFINED_COLUMN),
							 errmsg("column \"%s\" does not exist",
									attribute->name)));
			}
			attform = (Form_pg_attribute) GETSTRUCT(atttuple);
			indexInfo->ii_KeyAttrNumbers[attn] = attform->attnum;
			atttype = attform->atttypid;
			ReleaseSysCache(atttuple);
		}
		else if (attribute->expr && IsA(attribute->expr, Var))
		{

			Var		   *var = (Var *) attribute->expr;

			indexInfo->ii_KeyAttrNumbers[attn] = var->varattno;
			atttype = get_atttype(relId, var->varattno);
		}
		else
		{

			Assert(attribute->expr != NULL);
			indexInfo->ii_KeyAttrNumbers[attn] = 0;
			indexInfo->ii_Expressions = lappend(indexInfo->ii_Expressions,
												attribute->expr);
			atttype = exprType(attribute->expr);


			if (contain_subplans(attribute->expr))
				ereport(ERROR,
						(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						 errmsg("cannot use subquery in index expression")));
			if (contain_agg_clause(attribute->expr))
				ereport(ERROR,
						(errcode(ERRCODE_GROUPING_ERROR),
				errmsg("cannot use aggregate function in index expression")));


			if (contain_mutable_functions(attribute->expr))
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
						 errmsg("functions in index expression must be marked IMMUTABLE")));
		}

		classOidP[attn] = GetIndexOpClass(attribute->opclass,
										  atttype,
										  accessMethodName,
										  accessMethodId);
		attn++;
	}
}
