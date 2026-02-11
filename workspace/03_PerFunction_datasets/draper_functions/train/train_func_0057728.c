GMT_geo_to_dms (double val, GMT_LONG n_items, double fact, GMT_LONG *d, GMT_LONG *m,  GMT_LONG *s,  GMT_LONG *ix)
{

	GMT_LONG minus;
	GMT_LONG isec, imin;
	double sec, fsec, min, fmin, step;

	minus = (val < 0.0);
	step = (fact == 0.0) ? GMT_CONV_LIMIT : 0.5 / fact;

	if (n_items == 3) {
		sec = GMT_DEG2SEC_F * fabs (val) + step;
		isec = (GMT_LONG)floor (sec);
		fsec = sec - (double)isec;
		*d = isec / GMT_DEG2SEC_I;
		isec -= ((*d) * GMT_DEG2SEC_I);
		*m = isec / GMT_MIN2SEC_I;
		isec -= ((*m) * GMT_MIN2SEC_I);
		*s = isec;
		*ix = (GMT_LONG)floor (fsec * fact);
	}
	else if (n_items == 2) {
		min = GMT_DEG2MIN_F * fabs (val) + step;
		imin = (GMT_LONG)floor (min);
		fmin = min - (double)imin;
		*d = imin / GMT_DEG2MIN_I;
		imin -= ((*d) * GMT_DEG2MIN_I);
		*m = imin;
		*s = 0;
		*ix = (GMT_LONG)floor (fmin * fact);
	}
	else {
		min = fabs (val) + step;
		imin = (GMT_LONG)floor (min);
		fmin = min - (double)imin;
		*d = imin;
		*m = 0;
		*s = 0;
		*ix = (GMT_LONG)floor (fmin * fact);
	}
	if (minus) {
		if (*d)
			*d = -(*d);
		else
			return (TRUE);
	}
	return (FALSE);
}
