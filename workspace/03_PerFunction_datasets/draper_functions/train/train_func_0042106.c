node_update_cmap(struct isl_sched_node *node)
{
	isl_mat *H, *Q;
	int n_row = isl_mat_rows(node->sched);

	H = isl_mat_sub_alloc(node->sched, 0, n_row,
			      1 + node->nparam, node->nvar);

	H = isl_mat_left_hermite(H, 0, NULL, &Q);
	isl_mat_free(node->cmap);
	node->cmap = isl_mat_transpose(Q);
	node->rank = isl_mat_initial_non_zero_cols(H);
	isl_mat_free(H);

	if (!node->cmap || node->rank < 0)
		return -1;
	return 0;
}
