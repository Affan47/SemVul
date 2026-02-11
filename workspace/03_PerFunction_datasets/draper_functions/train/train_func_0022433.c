remove_nans(int size_in, double *xin, int *size_out, double **xout) {
    int no_valids = 0,
        ox        = 0,
        i         = 0;

    KMCLIPM_TRY
    {
        for (i = 0; i < size_in; i++) {
            if ((kmclipm_is_nan_or_inf(xin[i]) == 0)) {
                no_valids++;
            }
        }
        *size_out = no_valids;
        KMCLIPM_TRY_EXIT_IFN(
                *xout =  (double *) cpl_calloc(no_valids, sizeof(double)));

        ox = 0;
        for (i = 0; i < size_in; i++) {
            if ((kmclipm_is_nan_or_inf(xin[i]) == 0)) {
                (*xout)[ox] = xin[i];
                ox++;
            }
        }
    }
    KMCLIPM_CATCH
    {
    }

}
