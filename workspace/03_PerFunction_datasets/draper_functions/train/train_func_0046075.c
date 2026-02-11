nls_calc_approx (int m, int n, double *x, double *fvec,
		 int *iflag, void *p)
{
    int erru, errc, err;


    err = erru = update_coeff_values(x, p);


    if (!err) {
	err = errc = nl_function_calc(fvec, p);
    }

    if (err) {

	fprintf(stderr, "nls_calc_approx: got error %d from %s\n",
		err, (erru)? "update_coeff_values" :
		"nl_function_calc");
	*iflag = -1;
    }

    return 0;
}
