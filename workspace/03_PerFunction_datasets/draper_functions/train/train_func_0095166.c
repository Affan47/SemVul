deviceCallbackLoadVariable(devicePrivate_ *p, variable_ *variable,
		double R)
{

	ReturnErrIf(nodeDataPlus(variable->nodeRX, -(R - variable->R)));
	variable->R = R;


	p->VeqCalc -= R * rowGetSolution(variable->row);
	ReturnErrIf(isnan(p->VeqCalc));

	return 0;
}
