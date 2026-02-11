simulatorAddTLineW(simulator_ *r,
	char *refdes,
	char *nodes[], int nNodes,
	int *M, double *len,
	double **L0, double **C0, double **R0, double **G0, double **Rs,
	double **Gd, double *fgd, double *fK)
{
	device_ *device;

	ReturnErrIf(r == NULL);
	ReturnErrIf(r->locked, "Can't add a device to a simulator that has run.");


	device = deviceNewNPins(r->matrix, r->control, refdes, nodes, nNodes);
	ReturnErrIf(device == NULL);


	ReturnErrIf(deviceTLineWConfig(device, M, len, L0, C0, R0, G0, Rs,
			Gd, fgd, fK));


	ReturnErrIf(listAdd(r->devices, device, (listAdd_)deviceCheckDuplicate))

	return 0;
}
