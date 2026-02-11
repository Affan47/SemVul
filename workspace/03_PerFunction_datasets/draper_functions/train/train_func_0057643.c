getPoissonMG2(GridMG* p, GridMG* s, Condition c, SetBoundary set)
{
	if(!s) return getNullPoissonMG();


	PoissonMG * ps = g_malloc(sizeof(PoissonMG));
	ps->potential = p;
	ps->source = s;
	ps->diag = getDiagGridMG(ps->potential);

	ps->condition = c;
	ps->setBoundary = NULL;
	return ps;
}
