range_table_walker(List *rtable,
				   bool (*walker) (),
				   void *context,
				   int flags)
{
	ListCell   *rt;

	foreach(rt, rtable)
	{
		RangeTblEntry *rte = (RangeTblEntry *) lfirst(rt);

		switch (rte->rtekind)
		{
			case RTE_RELATION:
			case RTE_SPECIAL:

				break;
			case RTE_SUBQUERY:
				if (!(flags & QTW_IGNORE_RT_SUBQUERIES))
					if (walker(rte->subquery, context))
						return true;
				break;
			case RTE_JOIN:
				if (!(flags & QTW_IGNORE_JOINALIASES))
					if (walker(rte->joinaliasvars, context))
						return true;
				break;
			case RTE_FUNCTION:
				if (walker(rte->funcexpr, context))
					return true;
				break;
			case RTE_VALUES:
				if (walker(rte->values_lists, context))
					return true;
				break;
		}
	}
	return false;
}
