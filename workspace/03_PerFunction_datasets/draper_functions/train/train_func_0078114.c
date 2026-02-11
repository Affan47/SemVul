piecewiseInitialize(piecewise_ *r)
{
	int i;

	ReturnErrIf(r == NULL);

	if(r->m != NULL) {
		free(r->m);
	}

	r->xy = *r->xyPtr;
	r->length = *r->lengthPtr;

	for(i = 0; i < (r->length-1); i++) {
		ReturnErrIf(r->xy[i].x > r->xy[i+1].x, "%e > %e",
				r->xy[i].x, r->xy[i+1].x);
	}

	r->m = malloc(r->length * sizeof(double));
	ReturnErrIf(r->m == NULL);

	if(r->type == 'c') {
		ReturnErrIf(piecewiseCSplineInit(r));
	} else if(r->type == 'l') {
		ReturnErrIf(piecewiseLinearInit(r));
	} else {
		ReturnErr("Unsupported piece-wise type, must be c or l, not %c",
				r->type);
	}

	return 0;
}
