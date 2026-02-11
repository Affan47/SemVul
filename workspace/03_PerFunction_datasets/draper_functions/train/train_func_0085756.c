gwy_math_lin_solve_rewrite(gint n, gdouble *matrix,
                           gdouble *rhs,
                           gdouble *result)
{
    gint *perm;
    gint i, j, jj;

    g_return_val_if_fail(n > 0, NULL);
    g_return_val_if_fail(matrix && rhs, NULL);

    perm = g_new(gint, n);


    for (i = 0; i < n; i++) {
        gdouble *row = matrix + i*n;
        gdouble piv = 0;
        gint pivj = 0;


        for (j = 0; j < n; j++) {
            if (fabs(row[j]) > piv) {
                pivj = j;
                piv = fabs(row[j]);
            }
        }
        if (piv == 0.0) {
            g_warning("Singluar matrix");
            g_free(perm);
            return NULL;
        }
        piv = row[pivj];
        perm[i] = pivj;


        for (j = i+1; j < n; j++) {
            gdouble *jrow = matrix + j*n;
            gdouble q = jrow[pivj]/piv;

            for (jj = 0; jj < n; jj++)
                jrow[jj] -= q*row[jj];

            jrow[pivj] = 0.0;
            rhs[j] -= q*rhs[i];
        }
    }


    if (!result)
        result = g_new(gdouble, n);
    for (i = n-1; i >= 0; i--) {
        gdouble *row = matrix + i*n;
        gdouble x = rhs[i];

        for (j = n-1; j > i; j--)
            x -= result[perm[j]]*row[perm[j]];

        result[perm[i]] = x/row[perm[i]];
    }
    g_free(perm);

    return result;
}
