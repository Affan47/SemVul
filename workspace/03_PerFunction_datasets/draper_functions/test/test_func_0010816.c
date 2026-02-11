xy_get_sample (const double *y, const double *x,
			  int *t1, int *t2, int *n)
{
    int t, nxy, err = 0;

    for (t=*t1; t<=*t2; t++) {
	if (xna(x[t])) {
	    *t1 += 1;
	} else {
	    break;
	}
    }

    for (t=*t2; t>=*t1; t--) {
	if (xna(x[t])) {
	    *t2 -= 1;
	} else {
	    break;
	}
    }


    nxy = *n = 0;

    for (t=*t1; t<=*t2; t++) {
	if (!xna(x[t])) {
	    *n += 1;
	    if (!xna(y[t])) {
		nxy++;
	    }
	}
    }

    if (nxy < 16) {
	err = E_TOOFEW;
    }

    return err;
}
