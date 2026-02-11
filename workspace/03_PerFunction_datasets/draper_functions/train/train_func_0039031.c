CachedPlanGetTargetList(CachedPlanSource *plansource)
{
	Node	   *pstmt;


	Assert(plansource->magic == CACHEDPLANSOURCE_MAGIC);
	Assert(plansource->is_complete);


	if (plansource->resultDesc == NULL)
		return NIL;


	RevalidateCachedQuery(plansource);


	pstmt = PortalListGetPrimaryStmt(plansource->query_list);

	return FetchStatementTargetList(pstmt);
}
