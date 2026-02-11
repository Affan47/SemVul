forecast_stats (const double *y, const double *f,
			      int t1, int t2, gretlopt opt,
			      int *err)
{
    gretl_matrix *m = NULL;
    double ME, MSE, MAE, MPE, MAPE, U;
    double x, u[2];
    int nstats = (opt & OPT_D)? 9 : 6;
    int t, T = t2 - t1 + 1;

    for (t=t1; t<=t2; t++) {
	if (na(y[t]) || na(f[t])) {
	    *err = E_MISSDATA;
	    return NULL;
	}
    }

    m = gretl_column_vector_alloc(nstats);
    if (m == NULL) {
	*err = E_ALLOC;
	return NULL;
    }

    ME = MSE = MAE = MPE = MAPE = U = 0.0;
    u[0] = u[1] = 0.0;

    for (t=t1; t<=t2; t++) {
	x = y[t] - f[t];
	ME += x;
	MSE += x * x;
	MAE += fabs(x);
	if (y[t] == 0.0) {
	    MPE = MAPE = U = M_NA;
	} else {
	    MPE += 100 * x / y[t];
	    MAPE += 100 * fabs(x / y[t]);
	    if (t < t2) {
		x = (f[t+1] - y[t+1]) / y[t];
		u[0] += x * x;
		x = (y[t+1] - y[t]) / y[t];
		u[1] += x * x;
	    }
	}
    }

    ME /= T;
    MSE /= T;
    MAE /= T;

    if (!isnan(MPE)) {
	MPE /= T;
    }

    if (!isnan(MAPE)) {
	MAPE /= T;
    }

    if (!isnan(U) && u[1] > 0.0) {
	U = sqrt(u[0] / T) / sqrt(u[1] / T);
    }

    gretl_vector_set(m, 0, ME);
    gretl_vector_set(m, 1, MSE);
    gretl_vector_set(m, 2, MAE);
    gretl_vector_set(m, 3, MPE);
    gretl_vector_set(m, 4, MAPE);
    gretl_vector_set(m, 5, U);

    if (opt & OPT_D) {
	theil_decomp(m->val + 6, MSE, y, f, t1, t2);
    }

    return m;
}
