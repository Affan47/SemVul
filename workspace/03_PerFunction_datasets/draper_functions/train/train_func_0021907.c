ReleaseDbs(Tcl_Interp *interp, void *arg)
{
    Ns_DbHandle *handle;
    Tcl_HashEntry  *hPtr;
    Tcl_HashSearch  search;
    InterpData *idataPtr = arg;

    hPtr = Tcl_FirstHashEntry(&idataPtr->dbs, &search);
    while (hPtr != NULL) {
    	handle = Tcl_GetHashValue(hPtr);
   	Ns_DbPoolPutHandle(handle);
    	hPtr = Tcl_NextHashEntry(&search);
    }
    Tcl_DeleteHashTable(&idataPtr->dbs);
    Tcl_InitHashTable(&idataPtr->dbs, TCL_STRING_KEYS);
    idataPtr->cleanup = 0;
}
