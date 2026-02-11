fcast_transform (double xb, const MODEL *pmod,
			       int t, const double *offset,
			       double lmax)
{
    int ci = pmod->ci;
    double yf = xb;

    if (ci == TOBIT) {
	if (xb < 0.0) {
	    yf = 0.0;
	}
    } else if (ci == LOGIT) {
	if (gretl_model_get_int(pmod, "ordered")) {
	    yf = ordered_model_prediction(pmod, xb);
	} else {
	    yf = exp(xb) / (1.0 + exp(xb));
	}
    } else if (ci == PROBIT) {
	if (gretl_model_get_int(pmod, "ordered")) {
	    yf = ordered_model_prediction(pmod, xb);
	} else {
	    yf = normal_cdf(xb);
	}
    } else if (ci == LOGISTIC) {
	if (na(lmax)) {
	    yf = 1.0 / (1.0 + exp(-xb));
	} else {
	    yf = lmax / (1.0 + exp(-xb));
	}
    } else if (ci == POISSON || ci == NEGBIN) {
	if (offset != NULL) {
	    if (na(offset[t])) {
		yf = NADBL;
	    } else {
		yf = exp(xb + log(offset[t]));
	    }
	} else {
	    yf = exp(xb);
	}
    }

    return yf;
}
