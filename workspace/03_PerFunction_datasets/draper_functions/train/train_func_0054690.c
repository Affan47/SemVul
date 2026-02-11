get_key_neighbors(int nvk, double time, double range, int loop,
			 Keylist * karray[], Keylist ** km1, Keylist ** kp1,
			 Keylist ** kp2, Keylist ** km2, double *dt1,
			 double *dt2)
{
    int i;
    double len;

    *km1 = *kp1 = *kp2 = *km2 = NULL;
    *dt1 = *dt2 = 0.0;

    for (i = 0; i < nvk; i++) {
	if (time < karray[i]->pos) {
	    break;
	}
    }

    if (!i) {
	return (0.0);
    }

    if (i == nvk) {

	*km1 = karray[nvk - 1];
	return (0.0);
    }


    *km1 = karray[i - 1];
    *kp1 = karray[i];
    len = karray[i]->pos - karray[i - 1]->pos;

    if (i == 1) {

	if (loop) {
	    *km2 = karray[nvk - 2];
	    *kp2 = karray[(i + 1) % nvk];
	}
	else {
	    if (nvk > 2) {
		*kp2 = karray[i + 1];
	    }
	}
    }
    else if (i == nvk - 1) {

	if (loop) {
	    *km2 = nvk > 2 ? karray[i - 2] : karray[1];
	    *kp2 = karray[1];
	}
	else {
	    if (nvk > 2) {
		*km2 = karray[i - 2];
	    }
	}
    }
    else {
	*km2 = karray[i - 2];
	*kp2 = karray[i + 1];
    }

    *dt1 = (*km2) ? (*kp1)->pos - (*km2)->pos : len;
    *dt2 = (*kp2) ? (*kp2)->pos - (*km1)->pos : len;

    if (i == 1 && loop) {
	*dt1 += range;
    }

    if (i == nvk - 1 && loop) {
	*dt2 += range;
    }

    return (len);
}
