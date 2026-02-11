find_degenerated_axes(HklPseudoAxisEngine *self,
				  gsl_multiroot_function *func,
				  gsl_vector const *x, gsl_vector const *f,
				  int degenerated[])
{
	gsl_matrix *J;
	size_t i, j;

	memset(degenerated, 0, x->size * sizeof(int));
	J = gsl_matrix_alloc(x->size, f->size);

	gsl_multiroot_fdjacobian(func, x, f, GSL_SQRT_DBL_EPSILON, J);
	for(j=0; j<x->size && !degenerated[j]; ++j) {
		for(i=0; i<f->size; ++i)
			if (fabs(gsl_matrix_get(J, i, j)) > HKL_EPSILON)
				break;
		if (i == f->size)
			degenerated[j] = 1;
	}

#ifdef DEBUG
	fprintf(stdout, "\nLooks for degenerated axes\n");
	for(i=0; i<x->size; ++i)
		fprintf(stdout, " %d", degenerated[i]);
	for(i=0;i<x->size;++i) {
		fprintf(stdout, "\n   ");
		for(j=0;j<f->size;++j)
			fprintf(stdout, " %f", gsl_matrix_get(J, i, j));
	}
	fprintf(stdout, "\n");
#endif
	gsl_matrix_free(J);
}
