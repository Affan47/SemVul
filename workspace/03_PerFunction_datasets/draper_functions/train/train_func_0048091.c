compare2atomsUsingCenterOfGravity(const void* av,const void* bv)
{
	gint d;
	gdouble dd;
	gdouble xa,xb;
	MolSymAtom *a, *b;
	gdouble eps = 1e-3;


	a = (MolSymAtom*)av;
	b = (MolSymAtom*)bv;

	eps = (a->eps+b->eps)/2;

	d = a->type - b->type;
	if (d != 0) return d;


	xa = a->position[0]*a->position[0] + a->position[1]*a->position[1] + a->position[2]*a->position[2];
	xb = b->position[0]*b->position[0] + b->position[1]*b->position[1] + b->position[2]*b->position[2];

	if (fabs(xa-xb) > 2.*eps*MYMAX(xa,xb))	return (xa < xb) ? 1 : -1;

	dd = a->position[2] - b->position[2];
	if (dd != 0.0) return (dd > 0) ? 1 : -1;
	return 0;
}
