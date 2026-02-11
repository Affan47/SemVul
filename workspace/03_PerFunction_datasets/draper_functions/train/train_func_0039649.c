UpdateStringOfTime(objPtr)
    register Tcl_Obj *objPtr;
{
    Ns_Time *timePtr = (Ns_Time *) &objPtr->internalRep;
    size_t len;
    char buf[100];

    Ns_AdjTime(timePtr);
    if (timePtr->usec == 0) {
    	len = sprintf(buf, "%ld", timePtr->sec);
    } else {
    	len = sprintf(buf, "%ld:%ld", timePtr->sec, timePtr->usec);
    }
    objPtr->length = len;
    objPtr->bytes = ckalloc(len + 1);
    memcpy(objPtr->bytes, buf, len + 1);
}
