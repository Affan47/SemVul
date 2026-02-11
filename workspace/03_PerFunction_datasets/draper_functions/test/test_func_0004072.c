deviceNonlinearLoadVariable(variable_ *r, devicePrivate_ *p)
{
	double R;


	ReturnErrIf(calcDiff(p->calc, r->name, &R));
	ReturnErrIf(nodeDataPlus(r->nodeRX, -(R - r->R)));
	r->R = R;


	p->CeqCalc -= R * rowGetSolution(r->row);
	ReturnErrIf(isnan(p->CeqCalc));

	return 0;
}
