check_vals (const double *x, const double *y, int n)
{
    int ret = VARS_IDENTICAL;
    int t;

    for (t=0; t<n; t++) {
	if (floatneq(x[t], y[t])) {
	    if (na(x[t]) && !na(y[t])) {
		if (ret == VARS_IDENTICAL || ret == X_HAS_MISSING) {
		    ret = X_HAS_MISSING;
		} else {
		    ret = VARS_DIFFER;
		}
	    } else if (!na(x[t]) && na(y[t])) {
		if (ret == VARS_IDENTICAL || ret == Y_HAS_MISSING) {
		    ret = Y_HAS_MISSING;
		} else {
		    ret = VARS_DIFFER;
		}
	    } else {
		ret = VARS_DIFFER;
	    }

	}
	if (ret == VARS_DIFFER) {
	    break;
	}
    }

    return ret;
}
