deviceNonlinearCalculate(devicePrivate_ *p)
{
	p->In = rowGetSolution(p->rowR);
	ReturnErrIf(isnan(p->In));


	if(p->In == 0.0) {
		Debug("Open Nonlinear Current Source.");
		p->Ic = 0.0;
		return 0;
	}

	ReturnErrIf(calcSolve(p->calc, &p->Ic));

	return 0;
}
