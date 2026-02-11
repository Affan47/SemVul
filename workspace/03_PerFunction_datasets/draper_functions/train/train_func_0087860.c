_dxf_inittiming(void)
{
    if (!ti) {
	ti = (struct ti *) DXAllocateZero(sizeof(struct ti));
	if (!ti)
	    return ERROR;
	ti->procs = (struct _proc *)
	    DXAllocateZero(DXProcessors(0) * sizeof(struct _proc));
	if (!ti->procs) {
	    DXFree((Pointer)ti);
	    return ERROR;
	}
	_times(NULL, NULL, NULL);
    }
    return OK;
}
