netlibRPOLY(double *op, int *degree, double *zeror, double *zeroi)
{
	int info;
	rpoly_(op, degree, zeror, zeroi, &info);
	ReturnErrIf(info < 0, "info = %i", info);
	WarnIf(info > 0, "Less roots than order of approximation");
	return 0;
}
