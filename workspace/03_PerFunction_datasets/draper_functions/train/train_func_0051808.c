subtract(struct isl_mat *M, struct isl_mat **U,
	struct isl_mat **Q, unsigned row, unsigned i, unsigned j, isl_int m)
{
	int r;
	for (r = row; r < M->n_row; ++r)
		isl_int_submul(M->row[r][j], m, M->row[r][i]);
	if (U) {
		for (r = 0; r < (*U)->n_row; ++r)
			isl_int_submul((*U)->row[r][j], m, (*U)->row[r][i]);
	}
	if (Q) {
		for (r = 0; r < (*Q)->n_col; ++r)
			isl_int_addmul((*Q)->row[i][r], m, (*Q)->row[j][r]);
	}
}
