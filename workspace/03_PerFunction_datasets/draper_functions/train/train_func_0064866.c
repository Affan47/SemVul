DXRegisterWindowHandler(Error (*proc) (int, Pointer), Display *d, Pointer arg)
{
    int fd = ConnectionNumber(d);

    if (! DXRegisterInputHandler(proc, fd, arg))
	return ERROR;

#ifdef EXCEED_SOCKET

    if (! _dxf_SetExceedSocket(fd, (void *)d))
	    return ERROR;

#endif

    return OK;

}
