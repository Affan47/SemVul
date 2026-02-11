replace_outer_grouping(PlannerInfo *root, GroupingFunc *grp)
{
	Param	   *retval;
	PlannerParamItem *pitem;
	Index		levelsup;

	Assert(grp->agglevelsup > 0 && grp->agglevelsup < root->query_level);


	for (levelsup = grp->agglevelsup; levelsup > 0; levelsup--)
		root = root->parent_root;


	grp = (GroupingFunc *) copyObject(grp);
	IncrementVarSublevelsUp((Node *) grp, -((int) grp->agglevelsup), 0);
	Assert(grp->agglevelsup == 0);

	pitem = makeNode(PlannerParamItem);
	pitem->item = (Node *) grp;
	pitem->paramId = root->glob->nParamExec++;

	root->plan_params = lappend(root->plan_params, pitem);

	retval = makeNode(Param);
	retval->paramkind = PARAM_EXEC;
	retval->paramid = pitem->paramId;
	retval->paramtype = exprType((Node *) grp);
	retval->paramtypmod = -1;
	retval->paramcollid = InvalidOid;
	retval->location = grp->location;

	return retval;
}
