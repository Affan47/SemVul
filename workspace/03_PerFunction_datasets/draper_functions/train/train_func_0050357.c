deviceClassLoad(device_ *r)
{
	devicePrivate_ *p;
	ReturnErrIf(r == NULL);
	p = r->private;
	ReturnErrIf(p == NULL);

	Debug("Loading %s %s %p", r->class->type, r->refdes, r);


	ReturnErrIf(checklinearInitialize(p->checklinear, 0.0));
	p->Cc = 0.0;
	p->Cn = 0.0;
	p->Ceq = 0.0;
	p->CeqCalc = 0.0;


	ReturnErrIf(nodeDataSet(p->nodeRC, 1.0));
	ReturnErrIf(nodeDataSet(p->nodeCR, 1.0));

	ReturnErrIf(deviceNonlinearCalculate(p));
	ReturnErrIf(deviceNonlinearLoad(p));

	return 0;
}
