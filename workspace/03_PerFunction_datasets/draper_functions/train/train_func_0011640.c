ri_PlanCheck(const char *querystr, int nargs, Oid *argtypes,
			 RI_QueryKey *qkey, Relation fk_rel, Relation pk_rel,
			 bool cache_plan)
{
	SPIPlanPtr	qplan;
	Relation	query_rel;
	Oid			save_userid;
	int			save_sec_context;


	if (qkey->constr_queryno == RI_PLAN_CHECK_LOOKUPPK ||
		qkey->constr_queryno == RI_PLAN_CHECK_LOOKUPPK_NOCOLS)
		query_rel = pk_rel;
	else
		query_rel = fk_rel;


	GetUserIdAndSecContext(&save_userid, &save_sec_context);
	SetUserIdAndSecContext(RelationGetForm(query_rel)->relowner,
						   save_sec_context | SECURITY_LOCAL_USERID_CHANGE);


	qplan = SPI_prepare(querystr, nargs, argtypes);

	if (qplan == NULL)
		elog(ERROR, "SPI_prepare returned %d for %s", SPI_result, querystr);


	SetUserIdAndSecContext(save_userid, save_sec_context);


	if (cache_plan)
	{
		qplan = SPI_saveplan(qplan);
		ri_HashPreparedPlan(qkey, qplan);
	}

	return qplan;
}
