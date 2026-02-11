convert_EXISTS_sublink_to_join(PlannerInfo *root, SubLink *sublink,
							   bool under_not, Relids available_rels)
{
	JoinExpr   *result;
	Query	   *parse = root->parse;
	Query	   *subselect = (Query *) sublink->subselect;
	Node	   *whereClause;
	int			rtoffset;
	int			varno;
	Relids		clause_varnos;
	Relids		upper_varnos;

	Assert(sublink->subLinkType == EXISTS_SUBLINK);


	if (subselect->cteList)
		return NULL;


	subselect = (Query *) copyObject(subselect);


	if (!simplify_EXISTS_query(subselect))
		return NULL;


	if (subselect->jointree->fromlist == NIL)
		return NULL;


	whereClause = subselect->jointree->quals;
	subselect->jointree->quals = NULL;


	if (contain_vars_of_level((Node *) subselect, 1))
		return NULL;


	if (!contain_vars_of_level(whereClause, 1))
		return NULL;


	if (contain_volatile_functions(whereClause))
		return NULL;


	rtoffset = list_length(parse->rtable);
	OffsetVarNodes((Node *) subselect, rtoffset, 0);
	OffsetVarNodes(whereClause, rtoffset, 0);


	IncrementVarSublevelsUp((Node *) subselect, -1, 1);
	IncrementVarSublevelsUp(whereClause, -1, 1);


	clause_varnos = pull_varnos(whereClause);
	upper_varnos = NULL;
	while ((varno = bms_first_member(clause_varnos)) >= 0)
	{
		if (varno <= rtoffset)
			upper_varnos = bms_add_member(upper_varnos, varno);
	}
	bms_free(clause_varnos);
	Assert(!bms_is_empty(upper_varnos));


	if (!bms_is_subset(upper_varnos, available_rels))
		return NULL;


	parse->rtable = list_concat(parse->rtable, subselect->rtable);


	result = makeNode(JoinExpr);
	result->jointype = under_not ? JOIN_ANTI : JOIN_SEMI;
	result->isNatural = false;
	result->larg = NULL;

	if (list_length(subselect->jointree->fromlist) == 1)
		result->rarg = (Node *) linitial(subselect->jointree->fromlist);
	else
		result->rarg = (Node *) subselect->jointree;
	result->usingClause = NIL;
	result->quals = whereClause;
	result->alias = NULL;
	result->rtindex = 0;

	return result;
}
