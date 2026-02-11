deviceClassInitStep(device_ *r)
{
	devicePrivate_ *p;
	double i0;

	ReturnErrIf(r == NULL);
	p = r->private;
	ReturnErrIf(p == NULL);

	Debug("Initializing Stepping %s %s %p", r->class->type, r->refdes, r);


	i0 = rowGetSolution(p->rowR);
	ReturnErrIf(isnan(i0));

	ReturnErrIf(integratorInitialize(p->integrator, i0, p->L));

	return 0;
}
