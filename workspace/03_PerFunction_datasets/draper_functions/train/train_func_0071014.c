init_tour(PlannerInfo *root, Gene *tour, int num_gene)
{
	Gene	   *tmp;
	int			remainder;
	int			next,
				i;


	tmp = (Gene *) palloc(num_gene * sizeof(Gene));

	for (i = 0; i < num_gene; i++)
		tmp[i] = (Gene) (i + 1);

	remainder = num_gene - 1;

	for (i = 0; i < num_gene; i++)
	{

		next = geqo_randint(root, remainder, 0);

		tour[i] = tmp[next];

		tmp[next] = tmp[remainder];
		remainder--;
	}

	pfree(tmp);
}
