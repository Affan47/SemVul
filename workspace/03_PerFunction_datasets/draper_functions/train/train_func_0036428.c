init()
{
	GeneralMatrix ainvb(b);
	double rcond1;
	double rcondinf;
	a.multInvLeft2(ainvb, d, rcond1, rcondinf);
	pars.rcondA1 = rcond1;
	pars.rcondAI = rcondinf;
	bdecomp = new SchurDecompZero(ainvb);
	cdecomp = new SimilarityDecomp(c.getData().base(), c.numRows(), *(pars.bs_norm));
	cdecomp->check(pars, c);
	cdecomp->infoToPars(pars);
	if (*(pars.method) == SylvParams::recurse)
		sylv = new TriangularSylvester(*bdecomp, *cdecomp);
	else
		sylv = new IterativeSylvester(*bdecomp, *cdecomp);
}
