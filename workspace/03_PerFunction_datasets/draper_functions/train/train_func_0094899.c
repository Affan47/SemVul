edge_failure(Gene *gene, int index, Edge *edge_table, int num_gene)
{
	int			i;
	Gene		fail_gene = gene[index];
	int			remaining_edges = 0;
	int			four_count = 0;
	int			rand_decision;


	for (i = 1; i <= num_gene; i++)
	{
		if ((edge_table[i].unused_edges != -1) && (i != (int) fail_gene))
		{
			remaining_edges++;

			if (edge_table[i].total_edges == 4)
				four_count++;
		}
	}


	if (four_count != 0)
	{

		rand_decision = (int) geqo_randint(four_count - 1, 0);

		for (i = 1; i <= num_gene; i++)
		{

			if ((Gene) i != fail_gene &&
				edge_table[i].unused_edges != -1 &&
				edge_table[i].total_edges == 4)
			{

				four_count--;

				if (rand_decision == four_count)
					return (Gene) i;
			}
		}

		elog(LOG, "no edge found via random decision and total_edges == 4");
	}
	else if (remaining_edges != 0)
	{

		rand_decision = (int) geqo_randint(remaining_edges - 1, 0);

		for (i = 1; i <= num_gene; i++)
		{

			if ((Gene) i != fail_gene &&
				edge_table[i].unused_edges != -1)
			{

				remaining_edges--;

				if (rand_decision == remaining_edges)
					return i;
			}
		}

		elog(LOG, "no edge found via random decision with remaining edges");
	}


	else
	{


		for (i = 1; i <= num_gene; i++)
			if (edge_table[i].unused_edges >= 0)
				return (Gene) i;

		elog(LOG, "no edge found via looking for the last ununsed point");
	}


	elog(ERROR, "no edge found");
	return 0;
}
