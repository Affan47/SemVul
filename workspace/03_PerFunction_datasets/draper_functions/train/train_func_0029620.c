isl_mat_print_internal(__isl_keep isl_mat *mat, FILE *out, int indent)
{
	int i, j;

	if (!mat) {
		fprintf(out, "%*snull mat\n", indent, "");
		return;
	}

	if (mat->n_row == 0)
		fprintf(out, "%*s[]\n", indent, "");

	for (i = 0; i < mat->n_row; ++i) {
		if (!i)
			fprintf(out, "%*s[[", indent, "");
		else
			fprintf(out, "%*s[", indent+1, "");
		for (j = 0; j < mat->n_col; ++j) {
			if (j)
			    fprintf(out, ",");
			isl_int_print(out, mat->row[i][j], 0);
		}
		if (i == mat->n_row-1)
			fprintf(out, "]]\n");
		else
			fprintf(out, "]\n");
	}
}
