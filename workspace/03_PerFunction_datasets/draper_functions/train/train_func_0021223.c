Ns_TclDeAllocateInterp(Tcl_Interp *interp)
{
    NsInterp *itPtr;

    itPtr = NsGetInterpData(interp);
    if (itPtr == NULL) {
	Tcl_DeleteInterp(interp);
    } else if (itPtr->conn == NULL) {
    	PushInterp(itPtr);
    }
}
