allocate_more_data_space (struct FILTER1D_INFO *F)
{
	GMT_LONG	i;

	for (i = 0; i < F->n_cols; i++) F->data[i] = (double *) GMT_memory ((void *)F->data[i], (size_t)F->n_row_alloc, sizeof(double), GMT_program);
}
