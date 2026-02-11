icmDescStruct_allocate(
	icmDescStruct *p
) {
	int rv;

	if ((rv = p->device.allocate((icmBase *)&p->device)) != 0) {
		return rv;
	}
	if ((rv = p->model.allocate((icmBase *)&p->model)) != 0) {
		return rv;
	}
	return 0;
}
