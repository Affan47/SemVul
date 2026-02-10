find_placeholder_info(PlannerInfo *root, PlaceHolderVar *phv)
{
	PlaceHolderInfo *phinfo;
	ListCell   *lc;


	Assert(phv->phlevelsup == 0);

	foreach(lc, root->placeholder_list)
	{
		phinfo = (PlaceHolderInfo *) lfirst(lc);
		if (phinfo->phid == phv->phid)
			return phinfo;
	}


	phinfo = makeNode(PlaceHolderInfo);

	phinfo->phid = phv->phid;
	phinfo->ph_var = copyObject(phv);
	phinfo->ph_eval_at = pull_varnos((Node *) phv);

	phinfo->ph_needed = NULL;
	phinfo->ph_may_need = NULL;

	phinfo->ph_width = get_typavgwidth(exprType((Node *) phv->phexpr),
									   exprTypmod((Node *) phv->phexpr));

	root->placeholder_list = lappend(root->placeholder_list, phinfo);

	return phinfo;
}
