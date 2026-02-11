simulatorSolve(simulator_ *r, int interationLimit)
{
	int count = 0;
	int linear;

	ReturnErrIf(r == NULL);
	ReturnErrIf(interationLimit < 1);

	ReturnErrIf(matrixSolve(r->matrix));

	while(count++ < interationLimit) {
		linear = 1;
		ReturnErrIf(listExecute(r->devices, (listExecute_)deviceLinearize,
				&linear))
		if(linear)
			break;
		ReturnErrIf(matrixSolveAgain(r->matrix));
	};

	if(count == interationLimit) {
		Warn("Failed to Linearize Circuit");
	}

	return count;
}
