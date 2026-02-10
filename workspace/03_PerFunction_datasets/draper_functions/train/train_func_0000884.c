polynomial_irreg_reg_nonans(
        int nin, double *xi,
        double *yi,
        int nout, double xo0, double dxo,
        int order) {
    double *tmpVals = NULL,
           *x = NULL,
           *y = NULL;
    int new_size = 0;

    KMCLIPM_TRY
    {
        remove_2nans(nin, xi, yi, &new_size, &x, &y);
        tmpVals = polynomial_irreg_reg(new_size, x, y,
                nout, xo0, dxo, order);
        cpl_free(x); cpl_free(y);
    }
    KMCLIPM_CATCH
    {
    }
    return tmpVals;
}
