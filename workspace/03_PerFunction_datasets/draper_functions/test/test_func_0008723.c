giraffe_matrix_dump(const cpl_matrix *matrix, cxint max_rows)
{

    cxint i;
    cxint j;
    cxint k;
    cxint nc;
    cxint nr;
    cxint ncw;

    const cxdouble *pd_m = NULL;

    cx_string *buffer = NULL;
    cx_string *tmp = NULL;

    if (matrix == NULL) {
        return;
    }

    pd_m = cpl_matrix_get_data_const(matrix);

    nr = cpl_matrix_get_nrow(matrix);
    nc = cpl_matrix_get_ncol(matrix);

    if (nr > max_rows) {
        nr = max_rows;
    }

    buffer = cx_string_new();
    tmp = cx_string_new();


    for (i = 0; i < nc; i++) {
        ncw = cx_string_sprintf(tmp, "      %d", i);
        cx_string_append(buffer, cx_string_get(tmp));
    }

    cpl_msg_debug("", "%s", cx_string_get(buffer));


    for (k = 0, i = 0; i < nr; i++) {
        ncw = cx_string_sprintf(buffer,"  %d", i);
        for (j = 0; j < nc; j++, k++) {
            ncw = cx_string_sprintf(tmp, " %+18.12f", pd_m[k]);
            cx_string_append(buffer, cx_string_get(tmp));
        }

        cpl_msg_debug("", "%s", cx_string_get(buffer));
    }

    cx_string_delete(tmp);
    cx_string_delete(buffer);

    return;

}
