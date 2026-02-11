get_baserel_parampathinfo(PlannerInfo *root, RelOptInfo *baserel,
						  Relids required_outer)
{
	ParamPathInfo *ppi;
	Relids		joinrelids;
	List	   *pclauses;
	double		rows;
	ListCell   *lc;


	if (bms_is_empty(required_outer))
		return NULL;

	Assert(!bms_overlap(baserel->relids, required_outer));


	foreach(lc, baserel->ppilist)
	{
		ppi = (ParamPathInfo *) lfirst(lc);
		if (bms_equal(ppi->ppi_req_outer, required_outer))
			return ppi;
	}


	joinrelids = bms_union(baserel->relids, required_outer);
	pclauses = NIL;
	foreach(lc, baserel->joininfo)
	{
		RestrictInfo *rinfo = (RestrictInfo *) lfirst(lc);

		if (join_clause_is_movable_into(rinfo,
										baserel->relids,
										joinrelids))
			pclauses = lappend(pclauses, rinfo);
	}


	pclauses = list_concat(pclauses,
						   generate_join_implied_equalities(root,
															joinrelids,
															required_outer,
															baserel));


	rows = get_parameterized_baserel_size(root, baserel, pclauses);


	ppi = makeNode(ParamPathInfo);
	ppi->ppi_req_outer = required_outer;
	ppi->ppi_rows = rows;
	ppi->ppi_clauses = pclauses;
	baserel->ppilist = lappend(baserel->ppilist, ppi);

	return ppi;
}
