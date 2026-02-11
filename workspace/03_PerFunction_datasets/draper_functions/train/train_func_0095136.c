process(void)
{


    int nrows,
      ncols,
      nn;

    double *data[2];


    nrows = G_window_rows();
    ncols = G_window_cols();

    nn = G_math_max_pow2(MAX(nrows, ncols));


    if (nn * nn * sizeof(double) < 1)
	G_fatal_error(_("Unable to allocate data buffer. "
			"Check current region with g.region."));

    data[0] = (double *)G_malloc(nn * nn * sizeof(double));
    data[1] = (double *)G_malloc(nn * nn * sizeof(double));


    specsyn(data, nn);

    G_free(data[0]);
    G_free(data[1]);

    return 0;
}
