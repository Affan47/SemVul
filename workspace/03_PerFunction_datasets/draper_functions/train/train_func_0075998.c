convert_ANY_sublink_to_join(PlannerInfo *root, SubLink *sublink,
							Relids available_rels)
{
	JoinExpr   *result;
	Query	   *parse = root->parse;
	Query	   *subselect = (Query *) sublink->subselect;
	Relids		upper_varnos;
	int			rtindex;
	RangeTblEntry *rte;
	RangeTblRef *rtr;
	List	   *subquery_vars;
	Node	   *quals;

	Assert(sublink->subLinkType == ANY_SUBLINK);


	if (contain_vars_of_level((Node *) subselect, 1))
		return NULL;


	upper_varnos = pull_varnos(sublink->testexpr);
	if (bms_is_empty(upper_varnos))
		return NULL;


	if (!bms_is_subset(upper_varnos, available_rels))
		return NULL;


	if (contain_volatile_functions(sublink->testexpr))
		return NULL;


	rte = addRangeTableEntryForSubquery(NULL,
										subselect,
										makeAlias("ANY_subquery", NIL),
										false);
	parse->rtable = lappend(parse->rtable, rte);
	rtindex = list_length(parse->rtable);


	rtr = makeNode(RangeTblRef);
	rtr->rtindex = rtindex;


	subquery_vars = generate_subquery_vars(root,
										   subselect->targetList,
										   rtindex);


	quals = convert_testexpr(root, sublink->testexpr, subquery_vars);


	result = makeNode(JoinExpr);
	result->jointype = JOIN_SEMI;
	result->isNatural = false;
	result->larg = NULL;
	result->rarg = (Node *) rtr;
	result->using = NIL;
	result->quals = quals;
	result->alias = NULL;
	result->rtindex = 0;

	return result;
}
