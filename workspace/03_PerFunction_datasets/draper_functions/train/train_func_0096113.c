xyzoptfunc(void *cntx, double *v) {
	out_b2a_callback *p = (out_b2a_callback *)cntx;
	double swxyz[3], jab[3], dev[MAX_CHAN];
	double rv;
	int rc;

	rv = 2.0 - v[0];


	if (v[0] > 1.0) {
		rv += 1000.0;
		return rv;
	}
	if (v[0] < 0.0) {
		rv += 100.0;
		return rv;
	}
	swxyz[0] = v[0] * p->swxyz[0];
	swxyz[1] = v[0] * p->swxyz[1];
	swxyz[2] = v[0] * p->swxyz[2];


	p->ox->cam->XYZ_to_cam(p->ox->cam, jab, swxyz);


	rc = p->ox->inv_lookup(p->ox, dev, jab);

	if (rc != 0)
		rv += 500.0;


	return rv;
}
