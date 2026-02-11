DXAllocate(unsigned int n)
{
    Pointer x;

    if (!small && !DXinitdx())
	return NULL;
    if (trace && !DXTraceAlloc(trace))
	return NULL;

    for (;;) {

	if (n <= small->max_user) {
	    if ((x=amalloc(small, n))!=NULL)
		break;
	    DXResetError();
	}
	if ((x=amalloc(large, n))!=NULL)
	    break;

#if NORECURSE
	if (small->scavenger_running)
	    return NULL;
#endif
	small->scavenger_running++;

	if (!_dxfscavenge(n)) {
	    small->scavenger_running = 0;
	    if (DXGetError() == ERROR_NONE)
		DXSetError(ERROR_NO_MEMORY, "cannot allocate %d bytes", n);
	    return NULL;
	}

	small->scavenger_running = 0;
	DXResetError();
    }

    if (FOUND(x))
	DXFoundAlloc();

    return x;
}
