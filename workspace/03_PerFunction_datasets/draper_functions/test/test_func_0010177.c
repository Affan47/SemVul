mos_hough_table(cpl_table *table, const char *x, const char *y)
{
    cpl_table *output;
    double    *xdata;
    double    *ydata;
    double    *xodata;
    double    *yodata;
    double     max;
    int        npoints;
    int        opoints;
    int        i, j, k;


    if (!cpl_table_has_valid(table, x))
        return NULL;

    npoints = cpl_table_get_nrow(table);
    opoints = npoints*(npoints-1)/2;

    output = cpl_table_new(opoints);
    cpl_table_new_column(output, "m", CPL_TYPE_DOUBLE);
    cpl_table_new_column(output, "q", CPL_TYPE_DOUBLE);

    xodata = cpl_table_get_data_double(output, "m");
    yodata = cpl_table_get_data_double(output, "q");

    cpl_table_cast_column(table, x, "x", CPL_TYPE_DOUBLE);
    cpl_table_cast_column(table, y, "y", CPL_TYPE_DOUBLE);

    max = cpl_table_get_column_max(table, "x");
    cpl_table_fill_invalid_double(table, "x", max + 1.0);
    max += 0.5;

    xdata = cpl_table_get_data_double(table, "x");
    ydata = cpl_table_get_data_double(table, "y");

    k = 0;
    for (i = 0; i < npoints; i++) {
        if (xdata[i] < max) {
            for (j = i+1; j < npoints; j++) {
                if (xdata[j] < max) {
                    cpl_table_set_double(output, "m", k,
                                (ydata[i]-ydata[j])/(xdata[i]-xdata[j]));
                    cpl_table_set_double(output, "q", k,
                                ydata[i] - xodata[k] * xdata[i]);
                    k++;
                }
            }
        }
    }

    if (k != opoints)
        printf("Assert k = %d, expected %d\n", k, opoints);

    cpl_table_erase_column(table, "x");
    cpl_table_erase_column(table, "y");

    return output;
}
