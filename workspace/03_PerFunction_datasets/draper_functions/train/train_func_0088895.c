build_physical_tlist(PlannerInfo *root, RelOptInfo *rel)
{
	List	   *tlist = NIL;
	Index		varno = rel->relid;
	RangeTblEntry *rte = planner_rt_fetch(varno, root);
	Relation	relation;
	Query	   *subquery;
	Var		   *var;
	ListCell   *l;
	int			attrno,
				numattrs;
	List	   *colvars;

	switch (rte->rtekind)
	{
		case RTE_RELATION:

			relation = heap_open(rte->relid, NoLock);

			numattrs = RelationGetNumberOfAttributes(relation);
			for (attrno = 1; attrno <= numattrs; attrno++)
			{
				Form_pg_attribute att_tup = relation->rd_att->attrs[attrno - 1];

				if (att_tup->attisdropped)
				{

					tlist = NIL;
					break;
				}

				var = makeVar(varno,
							  attrno,
							  att_tup->atttypid,
							  att_tup->atttypmod,
							  0);

				tlist = lappend(tlist,
								makeTargetEntry((Expr *) var,
												attrno,
												NULL,
												false));
			}

			heap_close(relation, NoLock);
			break;

		case RTE_SUBQUERY:
			subquery = rte->subquery;
			foreach(l, subquery->targetList)
			{
				TargetEntry *tle = (TargetEntry *) lfirst(l);


				var = makeVar(varno,
							  tle->resno,
							  exprType((Node *) tle->expr),
							  exprTypmod((Node *) tle->expr),
							  0);

				tlist = lappend(tlist,
								makeTargetEntry((Expr *) var,
												tle->resno,
												NULL,
												tle->resjunk));
			}
			break;

		case RTE_FUNCTION:
			expandRTE(rte, varno, 0, true  ,
					  NULL, &colvars);
			foreach(l, colvars)
			{
				var = (Var *) lfirst(l);


				if (!IsA(var, Var))
				{
					tlist = NIL;
					break;
				}

				tlist = lappend(tlist,
								makeTargetEntry((Expr *) var,
												var->varattno,
												NULL,
												false));
			}
			break;

		case RTE_VALUES:
			expandRTE(rte, varno, 0, false  ,
					  NULL, &colvars);
			foreach(l, colvars)
			{
				var = (Var *) lfirst(l);

				tlist = lappend(tlist,
								makeTargetEntry((Expr *) var,
												var->varattno,
												NULL,
												false));
			}
			break;

		default:

			elog(ERROR, "unsupported RTE kind %d in build_physical_tlist",
				 (int) rte->rtekind);
			break;
	}

	return tlist;
}
