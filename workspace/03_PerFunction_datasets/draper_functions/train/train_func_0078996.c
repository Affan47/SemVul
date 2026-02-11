LookupQueue(Tcl_Interp       *interp,
                       CONST char       *queueId,
                       JobQueue        **queuePtr,
                       int              locked)
{
    Tcl_HashEntry *hPtr;

    if (!locked)
        Ns_MutexLock(&tp.queuelock);

    *queuePtr = NULL;

    hPtr = Tcl_FindHashEntry(&tp.queues, queueId);
    if (hPtr != NULL) {
	*queuePtr = Tcl_GetHashValue(hPtr);
        Ns_MutexLock(&(*queuePtr)->lock);
        ++((*queuePtr)->refCount);
    }

    if (!locked)
        Ns_MutexUnlock(&tp.queuelock);

    if (*queuePtr == NULL) {
        if (interp != NULL) {
            Tcl_AppendResult(interp, "no such queue: ", queueId, NULL);
        }
        return TCL_ERROR;
    }
    return TCL_OK;
}
