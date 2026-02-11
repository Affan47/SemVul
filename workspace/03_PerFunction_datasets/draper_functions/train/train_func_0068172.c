extract_query_dependencies(List *queries,
						   List **relationOids,
						   List **invalItems)
{
	PlannerGlobal glob;


	MemSet(&glob, 0, sizeof(glob));
	glob.type = T_PlannerGlobal;
	glob.relationOids = NIL;
	glob.invalItems = NIL;

	(void) extract_query_dependencies_walker((Node *) queries, &glob);

	*relationOids = glob.relationOids;
	*invalItems = glob.invalItems;
}
