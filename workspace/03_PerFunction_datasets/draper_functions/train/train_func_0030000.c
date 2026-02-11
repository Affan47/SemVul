inheritance_planner(PlannerInfo *root)
{
	Query	   *parse = root->parse;
	int			parentRTindex = parse->resultRelation;
	List	   *subplans = NIL;
	List	   *resultRelations = NIL;
	List	   *returningLists = NIL;
	List	   *rtable = NIL;
	List	   *rowMarks;
	List	   *tlist;
	PlannerInfo subroot;
	ListCell   *l;

	foreach(l, root->append_rel_list)
	{
		AppendRelInfo *appinfo = (AppendRelInfo *) lfirst(l);
		Plan	   *subplan;


		if (appinfo->parent_relid != parentRTindex)
			continue;


		memcpy(&subroot, root, sizeof(PlannerInfo));
		subroot.parse = (Query *)
			adjust_appendrel_attrs((Node *) parse,
								   appinfo);
		subroot.init_plans = NIL;
		subroot.hasInheritedTarget = true;


		Assert(subroot.join_info_list == NIL);

		Assert(subroot.placeholder_list == NIL);


		subplan = grouping_planner(&subroot, 0.0  );


		if (is_dummy_plan(subplan))
			continue;


		if (subplans == NIL)
			rtable = subroot.parse->rtable;

		subplans = lappend(subplans, subplan);


		root->init_plans = list_concat(root->init_plans, subroot.init_plans);


		resultRelations = lappend_int(resultRelations, appinfo->child_relid);


		if (parse->returningList)
		{
			List	   *rlist;

			rlist = set_returning_clause_references(root->glob,
												subroot.parse->returningList,
													subplan,
													appinfo->child_relid);
			returningLists = lappend(returningLists, rlist);
		}
	}

	root->resultRelations = resultRelations;


	root->query_pathkeys = NIL;


	if (subplans == NIL)
	{
		root->resultRelations = list_make1_int(parentRTindex);

		tlist = preprocess_targetlist(root, parse->targetList);
		return (Plan *) make_result(root,
									tlist,
									(Node *) list_make1(makeBoolConst(false,
																	  false)),
									NULL);
	}


	parse->rtable = rtable;


	if (parse->rowMarks)
		rowMarks = NIL;
	else
		rowMarks = root->rowMarks;


	return (Plan *) make_modifytable(parse->commandType,
									 copyObject(root->resultRelations),
									 subplans,
									 returningLists,
									 rowMarks,
									 SS_assign_special_param(root));
}
