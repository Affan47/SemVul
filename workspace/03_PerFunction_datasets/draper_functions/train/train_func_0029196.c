line_search_backtracking(
    int n,
    lbfgsfloatval_t *x,
    lbfgsfloatval_t *f,
    lbfgsfloatval_t *g,
    lbfgsfloatval_t *s,
    lbfgsfloatval_t *stp,
    const lbfgsfloatval_t* xp,
    const lbfgsfloatval_t* gp,
    lbfgsfloatval_t *wp,
    callback_data_t *cd,
    const lbfgs_parameter_t *param
    )
{
    int count = 0;
    lbfgsfloatval_t width, dg;
    lbfgsfloatval_t finit, dginit = 0., dgtest;
    const lbfgsfloatval_t dec = 0.5, inc = 2.1;


    if (*stp <= 0.) {
        return LBFGSERR_INVALIDPARAMETERS;
    }


    vecdot(&dginit, g, s, n);


    if (0 < dginit) {
        return LBFGSERR_INCREASEGRADIENT;
    }


    finit = *f;
    dgtest = param->ftol * dginit;

    for (;;) {
        veccpy(x, xp, n);
        vecadd(x, s, *stp, n);


        *f = cd->proc_evaluate(cd->instance, x, g, cd->n, *stp);

        ++count;

        if (*f > finit + *stp * dgtest) {
            width = dec;
        } else {

            if (param->linesearch == LBFGS_LINESEARCH_BACKTRACKING_ARMIJO) {

                return count;
	        }


	        vecdot(&dg, g, s, n);
	        if (dg < param->wolfe * dginit) {
    		    width = inc;
	        } else {
		        if(param->linesearch == LBFGS_LINESEARCH_BACKTRACKING_WOLFE) {

		            return count;
		        }


		        if(dg > -param->wolfe * dginit) {
		            width = dec;
		        } else {

		            return count;
		        }
            }
        }

        if (*stp < param->min_step) {

            return LBFGSERR_MINIMUMSTEP;
        }
        if (*stp > param->max_step) {

            return LBFGSERR_MAXIMUMSTEP;
        }
        if (param->max_linesearch <= count) {

            return LBFGSERR_MAXIMUMLINESEARCH;
        }

        (*stp) *= width;
    }
}
