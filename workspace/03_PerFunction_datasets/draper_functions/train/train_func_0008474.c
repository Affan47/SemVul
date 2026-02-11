inline_set_returning_functions(PlannerInfo *root)
{
	ListCell   *rt;

	foreach(rt, root->parse->rtable)
	{
		RangeTblEntry *rte = (RangeTblEntry *) lfirst(rt);

		if (rte->rtekind == RTE_FUNCTION)
		{
			Query	   *funcquery;


			funcquery = inline_set_returning_function(root, rte);
			if (funcquery)
			{

				rte->rtekind = RTE_SUBQUERY;
				rte->subquery = funcquery;
				rte->funcexpr = NULL;
				rte->funccoltypes = NIL;
				rte->funccoltypmods = NIL;
				rte->funccolcollations = NIL;
			}
		}
	}
}
