pg_rewrite_queries(List *querytree_list)
{
	List	   *new_list = NIL;
	ListCell   *list_item;

	if (log_parser_stats)
		ResetUsage();


	foreach(list_item, querytree_list)
	{
		Query	   *querytree = (Query *) lfirst(list_item);

		if (Debug_print_parse)
			elog_node_display(DEBUG1, "parse tree", querytree,
							  Debug_pretty_print);

		if (querytree->commandType == CMD_UTILITY)
		{

			new_list = lappend(new_list, querytree);
		}
		else
		{

			List	   *rewritten = QueryRewrite(querytree);

			new_list = list_concat(new_list, rewritten);
		}
	}

	querytree_list = new_list;

	if (log_parser_stats)
		ShowUsage("REWRITER STATISTICS");

#ifdef COPY_PARSE_PLAN_TREES


	new_list = (List *) copyObject(querytree_list);

	if (!equal(new_list, querytree_list))
		elog(WARNING, "copyObject() failed to produce an equal parse tree");
	else
		querytree_list = new_list;
#endif

	if (Debug_print_rewritten)
		elog_node_display(DEBUG1, "rewritten parse tree", querytree_list,
						  Debug_pretty_print);

	return querytree_list;
}
