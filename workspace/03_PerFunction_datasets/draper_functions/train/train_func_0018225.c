simulatorPrintDevices(simulator_ *r)
{
	ReturnErrIf(r == NULL);
	ReturnErrIf(listExecute(r->devices, (listExecute_)devicePrint, NULL));
	return 0;
}
