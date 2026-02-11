is_independent(__isl_keep isl_mat *facets, int n, isl_int *f)
{
	int rank;

	if (isl_seq_first_non_zero(f, facets->n_col) < 0)
		return 0;

	isl_seq_cpy(facets->row[n], f, facets->n_col);
	facets->n_row = n + 1;
	rank = isl_mat_rank(facets);
	if (rank < 0)
		return -1;

	return rank == n + 1;
}
