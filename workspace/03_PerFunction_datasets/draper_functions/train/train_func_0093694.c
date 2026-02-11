FlushArray(Array *arrayPtr)
{
    Tcl_HashEntry *hPtr;
    Tcl_HashSearch search;

    hPtr = Tcl_FirstHashEntry(&arrayPtr->vars, &search);
    while (hPtr != NULL) {
	ns_free(Tcl_GetHashValue(hPtr));
	Tcl_DeleteHashEntry(hPtr);
	hPtr = Tcl_NextHashEntry(&search);
    }
}
