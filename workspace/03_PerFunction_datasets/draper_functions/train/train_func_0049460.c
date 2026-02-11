gretl_matrix_row_i_mean (const gretl_matrix *m, int i)
{
    double x = row_sum(m, i);

    if (!na(x)) {
	x /= (double) m->cols;
    }

    return x;
}
