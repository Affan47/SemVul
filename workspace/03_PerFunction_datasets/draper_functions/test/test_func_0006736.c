PopInterp(char *server)
{
    static Ns_Cs lock;
    NsServer *servPtr;
    NsInterp *itPtr;
    Tcl_HashEntry *hPtr;
    Tcl_Interp *interp;
    int epoch;


    servPtr = NsGetServer(server);
    if (servPtr == NULL) {
	return NULL;
    }
    Ns_RWLockRdLock(&servPtr->tcl.slock);
    epoch = servPtr->tcl.epoch;
    Ns_RWLockUnlock(&servPtr->tcl.slock);


    hPtr = GetCacheEntry(servPtr);
    if (epoch == 0) {

	itPtr = Tcl_GetHashValue(hPtr);
    } else {
    	NsInterp *validPtr = NULL;
    	while ((itPtr = Tcl_GetHashValue(hPtr)) != NULL) {
	    Tcl_SetHashValue(hPtr, itPtr->nextPtr);
	    if (itPtr->epoch != epoch) {
	        Ns_TclDestroyInterp(itPtr->interp);
	    } else {
	        itPtr->nextPtr = validPtr;
	    	validPtr = itPtr;
	    }
	}
    	itPtr = validPtr;
    }
    if (itPtr != NULL) {
	Tcl_SetHashValue(hPtr, itPtr->nextPtr);
    } else {
    	if (nsconf.tcl.lockoninit) {
	    Ns_CsEnter(&lock);
    	}
	interp = CreateInterp(servPtr);
	itPtr = NsGetInterpData(interp);
    	RunTraces(itPtr, NS_TCL_TRACE_CREATE);
    	if (nsconf.tcl.lockoninit) {
	    Ns_CsLeave(&lock);
    	}
    }
    itPtr->nextPtr = NULL;
    interp = itPtr->interp;


    (void) Tcl_AsyncInvoke(interp, TCL_OK);
    RunTraces(itPtr, NS_TCL_TRACE_ALLOCATE);
    if (itPtr->epoch != epoch) {
	itPtr->epoch = epoch;
    }
    return itPtr;
}
