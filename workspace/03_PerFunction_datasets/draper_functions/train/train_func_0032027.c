ForeachTrace(NsInterp *itPtr, int why, int append)
{
    Tcl_Interp *interp = itPtr->interp;
    TclTrace *tracePtr;


    Tcl_ResetResult(interp);
    Ns_RWLockRdLock(&itPtr->servPtr->tcl.tlock);
    switch (why) {
    case NS_TCL_TRACE_FREECONN:
    case NS_TCL_TRACE_DEALLOCATE:
    case NS_TCL_TRACE_DELETE:
    	tracePtr = itPtr->servPtr->tcl.lastTracePtr;
	while (tracePtr != NULL) {
	    if (tracePtr->proc == EvalTrace && (tracePtr->when & why)) {
		DoTrace(interp, tracePtr, append);
	    }
	    tracePtr = tracePtr->prevPtr;
	}
    	tracePtr = itPtr->servPtr->tcl.lastTracePtr;
	while (tracePtr != NULL) {
	    if (tracePtr->proc != EvalTrace && (tracePtr->when & why)) {
		DoTrace(interp, tracePtr, append);
	    }
	    tracePtr = tracePtr->prevPtr;
	}
	break;

    default:
    	tracePtr = itPtr->servPtr->tcl.firstTracePtr;
    	while (tracePtr != NULL) {
	    if (tracePtr->proc != EvalTrace && (tracePtr->when & why)) {
		DoTrace(interp, tracePtr, append);
	    }
	    tracePtr = tracePtr->nextPtr;
	}
    	tracePtr = itPtr->servPtr->tcl.firstTracePtr;
    	while (tracePtr != NULL) {
	    if (tracePtr->proc == EvalTrace && (tracePtr->when & why)) {
		DoTrace(interp, tracePtr, append);
	    }
	    tracePtr = tracePtr->nextPtr;
	}
	break;
    }
    Ns_RWLockUnlock(&itPtr->servPtr->tcl.tlock);
    if (!append) {
	Tcl_ResetResult(interp);
    }
}
