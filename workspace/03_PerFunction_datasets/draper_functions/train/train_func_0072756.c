simulatorAddCallbackSource(simulator_ *r,
		char *refdes,
		char *pNode, char *nNode,
		char type, char *variables[], double values[], double derivs[],
		int numVariables, simulatorCallback_ callback, void*private)
{
	device_ *device;

	ReturnErrIf(r == NULL);
	ReturnErrIf(r->locked, "Can't add a device to a simulator that has run.");


	device = deviceNew2Pins(r->matrix, r->control, refdes, pNode, nNode);
	ReturnErrIf(device == NULL);


	if(tolower(type) == 'i') {
		ReturnErrIf(deviceCallbackCurrentConfig(device, variables, values,
				derivs, numVariables, 	callback, private));
	} else if(tolower(type) == 'v') {
		ReturnErrIf(deviceCallbackVoltageConfig(device, variables, values,
				derivs, numVariables, callback, private));
	} else {
		ReturnErr("Call-Back Source type must be either i or v, not %c", type);
	}


	ReturnErrIf(listAdd(r->devices, device, (listAdd_)deviceCheckDuplicate))

	return 0;
}
