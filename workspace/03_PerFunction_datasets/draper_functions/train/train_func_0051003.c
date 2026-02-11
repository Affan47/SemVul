NsTclCacheNamesCmd(ClientData dummy, Tcl_Interp *interp, int argc, char **argv)
{
    Tcl_HashEntry *hPtr;
    Tcl_HashSearch search;

    if (argc != 1) {
	Tcl_AppendResult(interp, "wrong # args: should be \"",
	    argv[0], "\"", NULL);
	return TCL_ERROR;
    }

    Ns_MutexLock(&lock);
    hPtr = Tcl_FirstHashEntry(&caches, &search);
    while (hPtr != NULL) {
	Tcl_AppendElement(interp, Tcl_GetHashKey(&caches, hPtr));
	hPtr = Tcl_NextHashEntry(&search);
    }
    Ns_MutexUnlock(&lock);

    return TCL_OK;
}
