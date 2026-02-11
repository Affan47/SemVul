print_rt(const List *rtable)
{
	const ListCell *l;
	int			i = 1;

	printf("resno\trefname  \trelid\tinFromCl\n");
	printf("-----\t---------\t-----\t--------\n");
	foreach(l, rtable)
	{
		RangeTblEntry *rte = lfirst(l);

		switch (rte->rtekind)
		{
			case RTE_RELATION:
				printf("%d\t%s\t%u\t%c",
					   i, rte->eref->aliasname, rte->relid, rte->relkind);
				break;
			case RTE_SUBQUERY:
				printf("%d\t%s\t[subquery]",
					   i, rte->eref->aliasname);
				break;
			case RTE_JOIN:
				printf("%d\t%s\t[join]",
					   i, rte->eref->aliasname);
				break;
			case RTE_FUNCTION:
				printf("%d\t%s\t[rangefunction]",
					   i, rte->eref->aliasname);
				break;
			case RTE_VALUES:
				printf("%d\t%s\t[values list]",
					   i, rte->eref->aliasname);
				break;
			case RTE_CTE:
				printf("%d\t%s\t[cte]",
					   i, rte->eref->aliasname);
				break;
			default:
				printf("%d\t%s\t[unknown rtekind]",
					   i, rte->eref->aliasname);
		}

		printf("\t%s\t%s\n",
			   (rte->inh ? "inh" : ""),
			   (rte->inFromCl ? "inFromCl" : ""));
		i++;
	}
}
