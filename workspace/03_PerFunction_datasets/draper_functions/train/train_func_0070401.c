expand_grouping_sets(List *groupingSets, int limit)
{
	List	   *expanded_groups = NIL;
	List	   *result = NIL;
	double		numsets = 1;
	ListCell   *lc;

	if (groupingSets == NIL)
		return NIL;

	foreach(lc, groupingSets)
	{
		List	   *current_result = NIL;
		GroupingSet *gs = lfirst(lc);

		current_result = expand_groupingset_node(gs);

		Assert(current_result != NIL);

		numsets *= list_length(current_result);

		if (limit >= 0 && numsets > limit)
			return NIL;

		expanded_groups = lappend(expanded_groups, current_result);
	}


	foreach(lc, (List *) linitial(expanded_groups))
	{
		result = lappend(result, list_union_int(NIL, (List *) lfirst(lc)));
	}

	for_each_cell(lc, lnext(list_head(expanded_groups)))
	{
		List	   *p = lfirst(lc);
		List	   *new_result = NIL;
		ListCell   *lc2;

		foreach(lc2, result)
		{
			List	   *q = lfirst(lc2);
			ListCell   *lc3;

			foreach(lc3, p)
			{
				new_result = lappend(new_result,
									 list_union_int(q, (List *) lfirst(lc3)));
			}
		}
		result = new_result;
	}

	if (list_length(result) > 1)
	{
		int			result_len = list_length(result);
		List	  **buf = palloc(sizeof(List *) * result_len);
		List	  **ptr = buf;

		foreach(lc, result)
		{
			*ptr++ = lfirst(lc);
		}

		qsort(buf, result_len, sizeof(List *), cmp_list_len_asc);

		result = NIL;
		ptr = buf;

		while (result_len-- > 0)
			result = lappend(result, *ptr++);

		pfree(buf);
	}

	return result;
}
