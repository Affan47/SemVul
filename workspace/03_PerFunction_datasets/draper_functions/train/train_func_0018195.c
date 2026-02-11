gnm_matrix_new (int rows, int cols)
{
	GnmMatrix *m = g_new (GnmMatrix, 1);
	int r;

	m->rows = rows;
	m->cols = cols;
	m->data = g_new (gnm_float *, rows);
	for (r = 0; r < rows; r++)
		m->data[r] = g_new (gnm_float, cols);

	return m;
}
