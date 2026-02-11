GMT_bin_input (FILE *fp, GMT_LONG *n, double **ptr)
{
	GMT_LONG status, n_use;

	GMT_io.status = 0;
	do {
		n_use = GMT_n_cols_needed_for_gaps (*n);
		if ((*GMT_read_binary) (fp, n_use)) return (-1);
		GMT_io.rec_no++;
		status = GMT_process_binary_input (n_use);
		if (status == 1) return (0);
	} while (status == 2);
	*ptr = GMT_curr_rec;
	if (GMT_gap_detected()) return (GMT_set_gap());
	GMT_io.pt_no++;

	return (*n);
}
