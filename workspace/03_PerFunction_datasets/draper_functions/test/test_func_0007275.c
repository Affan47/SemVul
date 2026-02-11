gretl_VAR_get_highest_variable (const GRETL_VAR *var)
{
    int i, vi, vmax = 0;

    if (var->ylist != NULL) {
	for (i=1; i<=var->ylist[0]; i++) {
	    vi = var->ylist[i];
	    if (vi > vmax) {
		vmax = vi;
	    }
	}
    }

    if (var->xlist != NULL) {
	for (i=1; i<=var->xlist[0]; i++) {
	    vi = var->xlist[i];
	    if (vi > vmax) {
		vmax = vi;
	    }
	}
    }

    if (var->rlist != NULL) {
	for (i=1; i<=var->rlist[0]; i++) {
	    vi = var->rlist[i];
	    if (vi > vmax) {
		vmax = vi;
	    }
	}
    }

    return vmax;
}
