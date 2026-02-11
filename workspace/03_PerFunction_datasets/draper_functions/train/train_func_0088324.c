Ns_TclEval(Ns_DString *dsPtr, char *server, char *script)
{
    int         retcode;
    Tcl_Interp *interp;
    CONST char *result;

    retcode = NS_ERROR;
    interp = Ns_TclAllocateInterp(server);
    if (interp != NULL) {
        if (Tcl_EvalEx(interp, script, -1, 0) != TCL_OK) {
	    result = Ns_TclLogError(interp);
        } else {
	    result = Tcl_GetStringResult(interp);
            retcode = NS_OK;
	}
	if (dsPtr != NULL) {
            Ns_DStringAppend(dsPtr, result);
        }
        Ns_TclDeAllocateInterp(interp);
    }
    return retcode;
}
