main(int argc, char *argv[])
{
	unsigned long offset;
	unsigned long long nranges;
	unsigned long nnodes;
	struct node *nodes;
	struct zipf_state zs;
	struct gauss_state gs;
	int i, j;

	if (parse_options(argc, argv))
		return 1;

	if (output_type != OUTPUT_CSV)
		printf("Generating %s distribution with %f input and %lu GB size and %lu block_size.\n", dist_types[dist_type], dist_val, gb_size, block_size);

	nranges = gb_size * 1024 * 1024 * 1024ULL;
	nranges /= block_size;

	if (dist_type == TYPE_ZIPF)
		zipf_init(&zs, nranges, dist_val, 1);
	else if (dist_type == TYPE_PARETO)
		pareto_init(&zs, nranges, dist_val, 1);
	else
		gauss_init(&gs, nranges, dist_val, 1);

	hash_bits = 0;
	hash_size = nranges;
	while ((hash_size >>= 1) != 0)
		hash_bits++;

	hash_size = 1 << hash_bits;

	hash = calloc(hash_size, sizeof(struct flist_head));
	for (i = 0; i < hash_size; i++)
		INIT_FLIST_HEAD(&hash[i]);

	nodes = malloc(nranges * sizeof(struct node));

	for (i = j = 0; i < nranges; i++) {
		struct node *n;

		if (dist_type == TYPE_ZIPF)
			offset = zipf_next(&zs);
		else if (dist_type == TYPE_PARETO)
			offset = pareto_next(&zs);
		else
			offset = gauss_next(&gs);

		n = hash_lookup(offset);
		if (n)
			n->hits++;
		else {
			hash_insert(&nodes[j], offset);
			j++;
		}
	}

	qsort(nodes, j, sizeof(struct node), node_cmp);
	nnodes = j;

	if (output_type == OUTPUT_CSV)
		output_csv(nodes, nnodes);
	else
		output_normal(nodes, nnodes, nranges);

	free(hash);
	free(nodes);
	return 0;
}
