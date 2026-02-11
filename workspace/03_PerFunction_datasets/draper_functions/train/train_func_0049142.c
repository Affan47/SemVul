Recv(Tcl_Interp *interp, Proxy *proxyPtr)
{
    Pool *poolPtr = proxyPtr->poolPtr;
    Proc *procPtr = proxyPtr->procPtr;
    Tcl_DString out;
    int result;
    Err err = ENone;

    if (proxyPtr->state == Idle) {
	err = EIdle;
    } else if (proxyPtr->state == Busy) {
	err = ENoWait;
    } else {
	Tcl_DStringInit(&out);
	if (!RecvBuf(procPtr, poolPtr->trecv, &out)) {
	    err = ERecv;
	} else if (!Import(interp, &out, &result)) {
	    err = EImport;
	} else {
	    proxyPtr->state = Idle;
	}
    	Tcl_DStringFree(&out);
    	Reset(proxyPtr);
    }
    if (err != ENone) {
	Tcl_AppendResult(interp, "could not receive result from proxy \"",
			 proxyPtr->id, "\": ", ProxyError(interp, err), NULL);
	return TCL_ERROR;
    }
    return result;
}
