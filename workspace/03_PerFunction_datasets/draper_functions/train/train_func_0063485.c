cpl_bivector_sort(cpl_bivector * self,
                                 const cpl_bivector * other,
                                 cpl_sort_direction dir,
                                 cpl_sort_mode mode)
{

    const cpl_size n = cpl_bivector_get_size(self);
    cpl_size     * perm;
    const double * data;
    int            reverse;
    cpl_size       i;
    cpl_error_code error = CPL_ERROR_NONE;


    cpl_ensure_code(self  != NULL, CPL_ERROR_NULL_INPUT);
    cpl_ensure_code(other != NULL, CPL_ERROR_NULL_INPUT);


    cpl_ensure_code(cpl_bivector_get_x_data_const(self) !=
                    cpl_bivector_get_y_data_const(self) ||
                    cpl_bivector_get_x_data_const(other) !=
                    cpl_bivector_get_y_data_const(other),
                    CPL_ERROR_UNSUPPORTED_MODE);
    cpl_ensure_code(cpl_bivector_get_size(other) == n,
                    CPL_ERROR_INCOMPATIBLE_INPUT);

    if (dir == CPL_SORT_ASCENDING) {
        reverse = 0;
    } else if (dir == CPL_SORT_DESCENDING) {
        reverse = 1;
    } else {
        return cpl_error_set_(CPL_ERROR_ILLEGAL_INPUT);
    }


    if (mode == CPL_SORT_BY_X) {
        data = cpl_bivector_get_x_data_const(other);
    } else if (mode == CPL_SORT_BY_Y) {
        data = cpl_bivector_get_y_data_const(other);
    } else {
        return cpl_error_set_(CPL_ERROR_UNSUPPORTED_MODE);
    }

    perm = (cpl_size*)cpl_malloc((size_t)n * sizeof(*perm));

    for (i = 0; i < n; i++) {
        perm[i] = i;
    }

    if (cpl_tools_sort_stable_pattern_double(data, n, reverse, 1, perm)) {
        error = cpl_error_set_where_();
    } else {
        double * dselfx = cpl_bivector_get_x_data(self);
        double * dselfy = cpl_bivector_get_y_data(self);
        const double * dotherx = cpl_bivector_get_x_data_const(other);
        const double * dothery = cpl_bivector_get_y_data_const(other);

        if (dselfx != dotherx && dselfy != dothery &&
            dselfx != dothery && dselfy != dotherx) {


            for (i = 0; i < n; i++) {
                dselfx[i] = dotherx[perm[i]];
                dselfy[i] = dothery[perm[i]];
            }

        } else if (cpl_tools_permute_double(perm, n, dselfx, dotherx,
                                            dselfy, dothery)) {
            error = cpl_error_set_where_();
        }
    }

    cpl_free(perm);
    return error;

}
